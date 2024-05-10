/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:37:09 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/10 16:57:51 by mhotting         ###   ########.fr       */
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

	if (
		redirection == NULL || info == NULL || info->error_infile
		|| redirection->type != REDIRECTION_TYPE_INFILE
	)
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
		|| (
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
static void	redirection_exec_dispatch(
	t_redirection *redirection, t_redirections_info *info, bool after_last_hd
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
}

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
 */
void	exec_redirection_list(
	t_minishell *shell, t_redirection_list *redirection_list
)
{
	t_list			*current;
	t_redirection	*redirection;
	ssize_t			position_last_heredoc;
	ssize_t			position;

	if (redirection_list == NULL)
		return ;
	current = redirection_list->redirections;
	position_last_heredoc = redirection_list->info.hdc_last_pos;
	position = 0;
	while (current != NULL)
	{
		redirection = (t_redirection *) current->content;
		if (redirection->type != REDIRECTION_TYPE_HEREDOC
			&& !expand_redirection(&redirection->filename, \
			O_QUOTE | O_PATH | O_VAR, shell))
		{
			exec_redir_set_error(redirection->type, &redirection_list->info);
			break ;
		}
		redirection_exec_dispatch(redirection, &(redirection_list->info), \
			(position > position_last_heredoc));
		position++;
		current = current->next;
	}
}
