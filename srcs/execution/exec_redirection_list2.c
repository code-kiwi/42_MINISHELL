/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_list2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:37:09 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/01 13:41:31 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include "libft.h"
#include "minishell.h"
#include "redirections.h"

/*
 *	Reads lines from STDIN_FILENO and writes them into the given fd_to_write
 *	When limiter is encountered, the reading process stops
 *	Returns true on success, false on error
 */
static bool	read_here_doc(char *limiter, int fd_to_write)
{
	char	*cur_line;

	if (limiter == NULL || fd_to_write < 0)
		return (false);
	cur_line = NULL;
	while (true)
	{
		if (ft_printf(MULTIPLE_LINE_PROMPT) == -1)
			return (false);
		free(cur_line);
		cur_line = get_next_line(STDIN_FILENO);
		if (cur_line == NULL)
		{
			if (errno != 0)
				return (false);
			handle_error(NULL, ERROR_HERE_DOC_EOF, 0);
			break ;
		}
		if (ft_strncmp(cur_line, limiter, ft_strlen(cur_line) - 1) == 0)
			break ;
		if (ft_dprintf(fd_to_write, "%s", cur_line) == -1)
		{
			free(cur_line);
			get_next_line(-1);
			return (false);
		}
	}
	get_next_line(-1);
	free(cur_line);
	return (true);
}

/*
 *	Executes a redirection of type REDIRECTION_TYPE_HEREDOC
 *	Opens a pipe and enables the user to write content into it, then closes
 *	the writing end of the pipe
 *	Assigns the info fd_stdin member the reading end of the pipe
 *	If a previous fd was assigned to info fd_stdin member, it is closed
 *	On error, nothing happens, all fds opened are closed
 */
void	exec_redirection_heredoc(
	t_redirection *redirection, t_redirections_info *info
)
{
	int	fd[2];

	if (
		redirection == NULL || info == NULL
		|| redirection->type != REDIRECTION_TYPE_HEREDOC
	)
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
	{
		fd_close(fd[0]);
		return ;
	}
	if (info->fd_stdin != FD_UNSET)
		fd_close_and_reset(&(info->fd_stdin));
	info->fd_stdin = fd[0];
}

/*
 *	Executes a redirection of type REDIRECTION_TYPE_INFILE
 *	If no error has been detected on stdin redirections, the redirection file is
 *	opened.
 *	Then, if the open() call failed, info infile error flag is set to true,
 *	the previous info fd_stdin member is closed if it was set
 *	If the open() call succeeded, the info fd_stdin member is updated (old one
 *	is closed if it was set)
 */
void	exec_redirection_infile(
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
	if (after_last_hd)
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
void	exec_redirection_out(
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
