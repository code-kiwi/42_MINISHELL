/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_expand_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:34:46 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/17 12:32:03 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include "libft.h"
#include "minishell.h"
#include "redirections.h"
#include "expansion.h"

/*
 *	Expands the content read from fd_in and writes the result into fd_out
 *	Returns true on SUCCESS, false on ERROR
*/
static bool	expand_hdc(t_minishell *shell, int fd_in, int fd_out)
{
	char	*line;

	while (true)
	{
		line = get_next_line(fd_in);
		if (line == NULL && errno != 0)
		{
			get_next_line(-1);
			return (false);
		}
		if (line == NULL)
			break ;
		expand_string(&line, shell, O_VAR | O_IGN_QUOTE);
		if (errno != 0 || ft_dprintf(fd_out, "%s", line) == -1)
		{
			get_next_line(-1);
			free(line);
			return (false);
		}
		free(line);
	}
	get_next_line(-1);
	return (true);
}

/*
 *	Expands the content of the heredoc when it is necessary
 *	Expand cases:
 *		- if the input redirection is a heredoc and not a file
 *		- if the heredoc limiter did not contain any double quote
 *		- if there was no error during the redirection process
 *	The function reads lines into the fd_stdin stored into redir_list info,
 *	expands them before writing the result into a new pipe.
 *	Then the redirection_list info fd_stdin member is updated
*/
void	exec_expand_heredoc(t_minishell *shell, t_redirection_list *redir_list)
{
	int		pipe_fds[2];
	bool	returned;

	if (
		shell == NULL || redir_list == NULL
		|| redirection_list_has_error(redir_list)
		|| !(redir_list->info.fdin_is_heredoc)
		|| !redir_list->info.hdc_needs_expansion
	)
		return ;
	if (pipe(pipe_fds) == -1)
		handle_error(shell, ERROR_MSG_PIPE, EXIT_FAILURE);
	returned = expand_hdc(shell, redir_list->info.fd_stdin, pipe_fds[1]);
	fd_close_and_reset(&(redir_list->info.fd_stdin));
	fd_close(pipe_fds[1]);
	if (!returned)
	{
		fd_close(pipe_fds[0]);
		redir_list->info.fd_stdin = FD_ERROR;
		redir_list->info.error_infile = true;
		handle_error(shell, ERROR_MSG_HEREDOC_EXP, EXIT_FAILURE);
	}
	redir_list->info.fd_stdin = pipe_fds[0];
}
