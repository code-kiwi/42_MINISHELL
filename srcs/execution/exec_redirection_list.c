/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:37:09 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/17 12:32:03 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>

#include "libft.h"
#include "minishell.h"
#include "execution.h"
#include "redirections.h"
#include "expansion.h"

/*
 *	Executes a redirection of type REDIRECTION_TYPE_INFILE
 *	If no error has been detected on stdin redirections, the redirection file is
 *	opened.
 *	Then, if the open() call failed, info infile error flag is set to true,
 *	the previous info fd_stdin member is closed if it was set
 *	If the open() call succeeded, the info fd_stdin member is updated (old one
 *	is closed if it was set)
 */
static void	exec_redirection_infile(
	t_redirection *redirection, t_redirections_info *info, bool after_last_hd
)
{
	int	fd;

	if (redirection == NULL || info == NULL || info->error_infile
		|| info->error_outfile || redirection->type != REDIRECTION_TYPE_INFILE)
		return ;
	fd = open(redirection->filename, O_RDONLY);
	if (fd == -1)
	{
		handle_error(NULL, redirection->filename, 0);
		info->error_infile = true;
		if (info->fd_stdin != FD_UNSET)
			fd_close_and_reset(&(info->fd_stdin));
		info->fd_stdin = FD_ERROR;
		return ;
	}
	if (!after_last_hd)
	{
		fd_close(fd);
		return ;
	}
	if (info->fd_stdin != FD_UNSET)
		fd_close_and_reset(&(info->fd_stdin));
	info->fd_stdin = fd;
	info->fdin_is_heredoc = false;
}

/*
 *	Executes a redirection of type REDIRECTION_TYPE_OUTFILE_<TRUNC|APPEND>
 *	If no error has been detected on stdout redirections, the redirection file
 *	is opened (open mode is set depending on the redirection type)
 *	Then, if the open() call failed, info outfile error flag is set to true,
 *	the previous info fd_stdout member is closed if it was set
 *	If the open() call succeeded, the info fd_stdout member is updated (old one
 *	is closed if it was set)
 */
static void	exec_redirection_out(
	t_redirection *redirection, t_redirections_info *info
)
{
	int	fd;

	if (
		redirection == NULL || info == NULL || info->error_outfile
		|| info->error_infile || (
			redirection->type != REDIRECTION_TYPE_OUTFILE_TRUNC
			&& redirection->type != REDIRECTION_TYPE_OUTFILE_APPEND)
	)
		return ;
	if (redirection->type == REDIRECTION_TYPE_OUTFILE_TRUNC)
		fd = open(redirection->filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(redirection->filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		handle_error(NULL, redirection->filename, 0);
		info->error_outfile = true;
		if (info->fd_stdout != FD_UNSET)
			fd_close_and_reset(&(info->fd_stdout));
		info->fd_stdout = FD_ERROR;
		return ;
	}
	if (info->fd_stdout != FD_UNSET)
		fd_close_and_reset(&(info->fd_stdout));
	info->fd_stdout = fd;
}

/*
 *	Executes a redirection depending on its type
 *	Calls the right executor, providing it the redirection information
 *	The after_last_hd flag is used to know if we are making redirections after
 *	the last here_doc redirection or not in order to avoid infile redirections
 *	to overwrite a here_doc redirection
 */
static void	redir_dispatch(
	t_minishell *shell, t_redirection *redirection, t_redirections_info *info,
	bool after_last_hd
)
{
	if (redirection == NULL)
		return ;
	if (redirection->type == REDIRECTION_TYPE_INFILE)
		exec_redirection_infile(redirection, info, after_last_hd);
	else if (
		redirection->type == REDIRECTION_TYPE_OUTFILE_TRUNC
		|| redirection->type == REDIRECTION_TYPE_OUTFILE_APPEND
	)
		exec_redirection_out(redirection, info);
	if (errno == ENOMEM)
		handle_error(shell, ERROR_MSG_MEM, EXIT_FAILURE);
	errno = 0;
}

/*
 *	Sets info error flags to true and the associated fd to FD_ERROR
 *	The right info member is selected according to the given type
*/
static void	exec_redir_set_error(
	enum e_redirection_type type, t_redirections_info *info
)
{
	if (info == NULL)
		return ;
	if (type == REDIRECTION_TYPE_INFILE)
	{
		info->error_infile = true;
		info->fd_stdin = FD_ERROR;
	}
	else
	{
		info->error_outfile = true;
		info->fd_stdin = FD_ERROR;
	}
}

/*
 *	Executes all the redirections stored into the given redirection list
 *	Stores the redirection information into info member of redirection_list
 *	Steps:
 *		- retrieves the last heredoc's position into the redirection list
 *		- executes the other redirections (using last heredoc's index in order
 *		to make stdin redirections logical: from left to right)
 *	After having performed all the redirections, calls the heredoc expansion
 *	(which will be done if necessary)
 */
void	exec_redirection_list(
	t_minishell *shell, t_redirection_list *redir_list
)
{
	t_list			*current;
	t_redirection	*redir;
	ssize_t			pos_last_hdc;
	ssize_t			pos;

	if (shell == NULL || redir_list == NULL)
		return ;
	current = redir_list->redirections;
	pos_last_hdc = redir_list->info.hdc_last_pos;
	pos = 0;
	while (current != NULL)
	{
		redir = (t_redirection *) current->content;
		if (redir->type != REDIRECTION_TYPE_HEREDOC && \
			!expand_redirection(&redir->filename, \
			O_QUOTE | O_PATH | O_VAR, shell))
		{
			exec_redir_set_error(redir->type, &redir_list->info);
			break ;
		}
		redir_dispatch(shell, redir, &(redir_list->info), (pos > pos_last_hdc));
		pos++;
		current = current->next;
	}
	exec_expand_heredoc(shell, redir_list);
}
