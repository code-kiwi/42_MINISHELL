/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:10:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/01 11:29:29 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/wait.h>
#include "minishell.h"
#include "pid_list.h"
#include <signal.h>
#include "signals.h"

void	kill_all_childs(t_pid_list *childs, t_minishell *shell)
{
	bool	error;

	error = false;
	while (childs != NULL)
	{
		if (childs->pid != PID_ERROR)
			error = ((kill(childs->pid, SIGINT) == -1) && errno != ESRCH)
				|| error;
		childs = childs->next;
	}
	if (error)
		handle_error(shell, KILL_ERROR, EXIT_FAILURE);
	if (errno == ESRCH)
		errno = 0;
}

/*
 *	Adds a pid to the given shell's pid list
 *	Returns true on SUCCESS, false on ERROR
 */
bool	t_minishell_add_pid(t_minishell *shell, pid_t pid)
{
	t_pid_list	*new;

	if (shell == NULL)
	{
		errno = EINVAL;
		return (false);
	}
	new = pid_list_new(pid);
	if (new == NULL)
		return (false);
	pid_list_add_back(&(shell->pid_list), new);
	return (true);
}

int	get_return_value(t_pid_list *current)
{
	int	status;

	if (waitpid(current->pid, &status, 0) == -1)
		return (-1);
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status) + 128);
	return (0);
}

/*
 *	Returns if the child have been interrupted
 *	Set the shell->status
 *	Clears the shell's pid_list member
 *	If the list is empty, returns EXIT_SUCCESS as a default value
 */
static bool	t_minishell_wait_pids(t_minishell *shell)
{
	t_pid_list	*current;
	bool		not_interrupted;

	if (shell == NULL)
		return (EXIT_FAILURE);
	current = shell->pid_list;
	not_interrupted = true;
	while (current != NULL)
	{
		if (current->pid == PID_ERROR && current->next == NULL)
			shell->status = EXIT_FAILURE;
		else if (current->pid != PID_ERROR)
		{
			shell->status = get_return_value(current);
			if (catch_sigint())
			{
				not_interrupted = false;
				kill_all_childs(shell->pid_list, shell);
			}
		}
		current = current->next;
	}
	pid_list_clear(&(shell->pid_list));
	return (not_interrupted);
}

/*
 *	Returns if the childs haven been interrupted
 *	If the shell's pid list is empty, the current shell's status is returned
 */
bool	t_minishell_set_exec_status(t_minishell *shell)
{
	int		not_interrupted;
	size_t	nb_pids;

	if (shell == NULL)
		return (EXIT_FAILURE);
	nb_pids = pid_list_size(shell->pid_list);
	if (nb_pids == 0)
		return (shell->status);
	set_interactive_mode(false);
	not_interrupted = t_minishell_wait_pids(shell);
	if (get_signal_error())
		handle_error(shell, SIGNAL_ERROR, EXIT_FAILURE);
	return (not_interrupted);
}
