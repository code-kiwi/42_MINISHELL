/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_list_hdcs.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:35:13 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/04 21:18:03 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"
#include "minishell.h"
#include "redirections.h"
#include "execution.h"

/*
 *	Executes the heredoc routine
 *	Calls the function that reads the user input
 *	Clears all the process resources
 *	Returns a status according to heredoc routine status of execution
 *	NB: this function is supposed to be called from a child process
 */
static void	exec_hdcs_handle_subprocess(
	t_minishell *shell, char *lim, int pipe_fds[2]
)
{
	int	status;

	if (shell == NULL || lim == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	//status = read_here_doc_NEW(lim, fds[1]);
	status = EXIT_FAILURE;
	fds_close_and_reset(pipe_fds);
	t_minishell_free(shell);
	exit(status);
}

/*
 *	Handles the main process routine after a heredoc subprocess execution
 *	Retrives the sub_process (pointed by pid) exit status:
 *		- If this one is valid, saves the pipe read fd into redirection info
 *		- If the exit status is not EXIT_SUCCESS:
 *			-> closes de pipe read end
 *			-> according to the type of exit status (interruption or not), sets
 *			the hdc_info flags
 */
static void	exec_hds_handle_mainprocess(
	pid_t pid, int pipe_fd_read, t_redirections_info *info,
	t_heredoc_exec_info *hdc_info
)
{
	int		status;
	bool	sig_interruption;

	if (info == NULL || hdc_info == NULL)
		return (hdc_info_set_error(hdc_info));
	status = get_return_value(pid, &sig_interruption);
	if (status == EXIT_SUCCESS)
		info->fd_stdin = pipe_fd_read;
	else
	{
		fd_close_and_reset(&pipe_fd_read);
		if (sig_interruption)
			hdc_info->interruption = true;
		else
			hdc_info->error_flag = true;
	}
}

/*
 *	Given a heredoc redirection executes the heredoc process
 *	Steps:
 *		- arg check
 *		- pipe opening (the heredoc input will be written into a pipe and the
 *		read end of the pipe will be used later to read the input)
 *		- forks in order to execute the heredoc routine into a subprocess
 *		- the main process retrives the child process' exit status in order to
 *		have information about the heredoc and save them into redirection info
 *		and hdc_info
 *	NB: redirection info will be used to store the reading end of the pipe
 *	NB: hdc_info will be used to store info about the heredoc execution (used to
 *	see if the heredoc process was interrupted by a signal or encountered an
 *	error)
 */
static void	exec_redirection_heredoc_NEW(
	t_minishell *shell, t_redirection *redir, t_redirections_info *info,
	t_heredoc_exec_info *hdc_info
)
{
	int		fds[2];
	pid_t	pid;

	if (
		redir == NULL || redir->type != REDIRECTION_TYPE_HEREDOC
		|| info == NULL || hdc_info == NULL
	)
		return (hdc_info_set_error(hdc_info));
	if (pipe(fds) == -1)
		return (hdc_info_set_error(hdc_info));
	pid = fork();
	if (pid == -1)
	{
		fds_close_and_reset(fds);
		return (hdc_info_set_error(hdc_info));
	}
	else if (pid == 0)
		exec_hdcs_handle_subprocess(shell, redir->filename, fds);
	fd_close(fds[1]);
	exec_hds_handle_mainprocess(pid, fds[0], info, hdc_info);
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
	while (redir_link != NULL && !hdc_info->error_flag && !hdc_info->interruption)
	{
		redir = (t_redirection *) redir_link->content;
		if (redir != NULL && redir->type == REDIRECTION_TYPE_HEREDOC)
		{
			exec_redirection_heredoc_NEW(shell, redir, &(redirection_list->info), hdc_info);
			redirection_list->info.hdc_last_pos = pos;
		}
		redir_link = redir_link->next;
		pos++;
	}
}
