/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection_list.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:37:09 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/12 10:15:06 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	read_here_doc(char *limiter, int fd_to_write)
{
	char	*cur_line;

	if (limiter == NULL || fd_to_write < 0)
		return (false);
	while (true)
	{
		if (ft_printf(MULTIPLE_LINE_PROMPT) == -1)
			return (false);
		cur_line = get_next_line(STDIN_FILENO);
		if (cur_line == NULL)
			continue ;
		if (ft_strncmp(cur_line, limiter, ft_strlen(cur_line) - 1) == 0)
			break ;
		if (ft_dprintf(fd_to_write, "%s", cur_line) == -1)
		{
			free(cur_line);
			get_next_line(-1);
			return (false);
		}
		free(cur_line);
	}
	get_next_line(-1);
	free(cur_line);
	return (true);
}

static void	exec_redirection_heredoc(
	t_redirection *redirection, t_redirections_info *info
)
{
	int	fd[2];

	if (redirection == NULL || info == NULL)
		return ;
	if (pipe(fd) == -1)
		return (handle_error(NULL, ERROR_MSG_PIPE, 0));
	if (!read_here_doc(redirection->filename, fd[1]))
	{
		fd_close(fd[0]);
		fd_close(fd[1]);
		return (handle_error(NULL, ERROR_MSG_HEREDOC, 0));
	}
	fd_close(fd[1]);
	if (info->error_infile)
		return (fd_close(fd[0]));
	if (info->fd_stdin != FD_UNSET)
		fd_close_and_reset(&(info->fd_stdin));
	info->fd_stdin = fd[0];
}

static void	exec_redirection_infile(
	t_redirection *redirection, t_redirections_info *info, bool after_last_hd
)
{
	int	fd;

	if (redirection == NULL || info == NULL || info->error_infile)
		return ;
	fd = open(redirection->filename, O_RDONLY);
	if (fd == -1)
	{
		handle_error(NULL, redirection->filename, 0);
		info->error_infile = true;
		info->fd_stdin = FD_ERROR;
		return ;
	}
	if (after_last_hd)
	{
		fd_close(fd);
		return ;
	}
	if (info->fd_stdin != FD_UNSET)
		fd_close_and_reset(&(info->fd_stdin));
	info->fd_stdin = fd;
}

static void	exec_redirection_out(
	t_redirection *redirection, t_redirections_info *info, bool trunc
)
{
	int	fd;

	if (redirection == NULL || info == NULL || info->error_outfile)
		return ;
	if (trunc)
		fd = open(redirection->filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(redirection->filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		info->error_outfile = true;
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
	else if (redirection->type == REDIRECTION_TYPE_OUTFILE_TRUNC)
		exec_redirection_out(redirection, info, true);
	else if (redirection->type == REDIRECTION_TYPE_OUTFILE_APPEND)
		exec_redirection_out(redirection, info, false);
}

/*
 *	Executes all the heredoc redirections from the given redirection list
 *	Returns the position (into the list) of the last heredoc redirection
 *	Returns -1 if no heredoc redirection has been encountered
 */
static ssize_t	exec_heredocs(t_list *redirections, t_redirections_info *info)
{
	ssize_t			position;
	ssize_t			last_hd_pos;
	t_redirection	*redirection;
	t_list			*current_red;

	if (redirections == NULL)
		return (-1);
	current_red = redirections;
	position = 0;
	last_hd_pos = -1;
	while (current_red != NULL)
	{
		redirection = (t_redirection *) current_red->content;
		if (redirection->type == REDIRECTION_TYPE_HEREDOC)
		{
			exec_redirection_heredoc(redirection, info);
			last_hd_pos = position;
		}
		position++;
		current_red = current_red->next;
	}
	return (last_hd_pos);
}

/*
 *	Executes all the redirections stored into the given redirection list
 *	Stores the redirection information into info member of redirection_list
 *	Steps:
 *		- executes all the heredoc redirections first
 *		- executes the other redirections (using last heredoc's index in order
 *		to make stdin redirections logical: from left to right)
 */
void	exec_redirection_list(t_redirection_list *redirection_list)
{
	t_list			*current;
	t_redirection	*redirection;
	ssize_t			position_last_heredoc;
	ssize_t			position;

	if (redirection_list == NULL)
		return ;
	current = redirection_list->redirections;
	position_last_heredoc = exec_heredocs(current, &(redirection_list->info));
	position = 0;
	while (current != NULL)
	{
		redirection = (t_redirection *) current->content;
		redirection_exec_dispatch(redirection, &(redirection_list->info), \
			(position_last_heredoc != -1 && position > position_last_heredoc));
		position++;
		current = current->next;
	}
}
