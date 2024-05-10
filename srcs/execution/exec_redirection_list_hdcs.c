/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_list_hdcs.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:35:13 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/08 01:54:59 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <errno.h>
#include "libft.h"
#include "redirections.h"
#include "execution.h"
#include "signals.h"
#include "expansion.h"

/*
 *	Handles NULL input when reading here_doc
 *	Cases:
 *		- errno != 0 means that something wrong happened
 *		- get_sigint() returns true when SIGINT has been catched, which means
 *		that the heredoc process has been stopped by the user
 *		- else the heredoc process has been stopped without the limiter
 *	Returns an integer according to the previous mentionned cases
 */
static int	read_here_doc_error(char *limiter)
{
	if (errno != 0 && errno != EINTR)
		return (EXIT_FAILURE);
	else if (get_sigint())
	{
		errno = 0;
		return (STATUS_SIGINT_STOP);
	}
	ft_dprintf(STDERR_FILENO, ERROR_HERE_DOC_EOF, limiter);
	return (EXIT_SUCCESS);
}

/*
 *	Reads the user input and writes it (adding a new line) into the given fd
 *	When the limiter is encountered, the reading process stops
 *	When the user adds EOF, the reading process stops (displaying a message)
 *	When the user sends SIGINT signal, the reading process stops
 *	Returns:
 *		- EXIT_SUCCESS on SUCCESS (reading process stopped by limiter or EOF)
 *		- EXIT_FAILURE on ERROR
 *		- STATUS_SIGINT_STOP on SIGINT user stop
 */
static int	read_here_doc(t_minishell *shell, char *limiter, int fd_to_write)
{
	char	*cur_line;

	if (limiter == NULL || fd_to_write < 0)
		return (EXIT_FAILURE);
	expand_string(&limiter, shell, O_QUOTE);
	if (errno != 0)
		return (EXIT_FAILURE);
	while (true)
	{
		cur_line = readline(HEREDOC_PROMPT);
		if (cur_line == NULL || get_sigint())
		{
			if (cur_line != NULL)
				free(cur_line);
			return (read_here_doc_error(limiter));
		}
		if (ft_strncmp(cur_line, limiter, ft_strlen(cur_line)) == 0)
			break ;
		expand_string(&cur_line, shell, O_VAR | O_IGN_QUOTE);
		if (errno != 0 || ft_dprintf(fd_to_write, "%s\n", cur_line) == -1)
			return (free(cur_line), EXIT_FAILURE);
		free(cur_line);
	}
	free(cur_line);
	return (EXIT_SUCCESS);
}

/*
 *	Given a heredoc redirection executes the heredoc process
 *	Steps:
 *		- arg check
 *		- pipe opening (the heredoc input will be written into a pipe and the
 *		read end of the pipe will be stored into redirection info in order to
 *		be used later to read the input)
 *		- Calls function that reads the user input for heredoc
 *		- According to the heredoc reading function returned status:
 *			-> EXIT_FAILURE: hdc_info error_flag is set to true
 *			-> STATUS_SIGINT_STOP: hdc_info interruption flag is set to true
 *			-> EXIT_SUCCESS: saves the pipe reading end into info->fd_stdin
 *	NB: Interactive mode is enabled before user input typing and disbaled right
 *	after in order to handle SIGINT
 *	NB: redirection info will be used to store the reading end of the pipe
 *	NB: hdc_info will be used to store info about the heredoc execution (used to
 *	see if the heredoc process was interrupted by a signal or encountered an
 *	error)
 */
static void	exec_redirection_heredoc(
	t_minishell *shell, t_redirection *redir, t_redirections_info *info,
	t_heredoc_exec_info *hdc_info
)
{
	int	pipe_fds[2];
	int	status;

	if (
		redir == NULL || redir->type != REDIRECTION_TYPE_HEREDOC
		|| info == NULL || hdc_info == NULL || pipe(pipe_fds) == -1
	)
		return (hdc_info_set_error(hdc_info));
	set_interactive_mode(true);
	status = read_here_doc(shell, redir->filename, pipe_fds[1]);
	set_interactive_mode(false);
	fd_close_and_reset(&pipe_fds[1]);
	if (status == EXIT_SUCCESS)
	{
		fd_close_and_reset(&(info->fd_stdin));
		info->fd_stdin = pipe_fds[0];
	}
	else
	{
		fd_close_and_reset(&pipe_fds[0]);
		if (status == STATUS_SIGINT_STOP)
			hdc_info->interruption = true;
		else
			hdc_info->error_flag = true;
	}
}

/*
 *	Given a list of redirection, executes all its heredocs
 *	The file descriptor into which the user input has been written and the
 *	heredoc position (index into the list) are then stored into the redirection
 *	list info member
 *	In case of ERROR, sets hdc_info's error member to true and returns
 */
void	exec_redirection_list_heredocs(
	t_minishell *shell, t_redirection_list *redirection_list,
	t_heredoc_exec_info *hdc_info
)
{
	t_list			*redir_link;
	t_redirection	*redir;
	ssize_t			pos;

	if (hdc_info == NULL || redirection_list == NULL)
		return (hdc_info_set_error(hdc_info));
	redir_link = redirection_list->redirections;
	pos = 0;
	while (
		redir_link != NULL && !hdc_info->error_flag && !hdc_info->interruption
	)
	{
		redir = (t_redirection *) redir_link->content;
		if (redir != NULL && redir->type == REDIRECTION_TYPE_HEREDOC)
		{
			exec_redirection_heredoc(shell, redir, \
				&redirection_list->info, hdc_info);
			redirection_list->info.hdc_last_pos = pos;
		}
		redir_link = redir_link->next;
		pos++;
	}
}
