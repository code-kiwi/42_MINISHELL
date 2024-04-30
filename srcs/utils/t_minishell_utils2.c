/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:10:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/30 18:22:44 by root             ###   ########.fr       */
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

void	kill_all_childs(t_pid_list *childs)
{
	while (childs != NULL)
	{
		if (childs->pid != PID_ERROR)
			kill(childs->pid, SIGINT);
		childs = childs->next;
	}
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

/*
 *	Returns the status from the execution of the process whose pid was saved
 *	into the shell's pid_list member
 *	Clears the shell's pid_list member
 *	If the list is empty, returns EXIT_SUCCESS as a default value
 */
static int	t_minishell_wait_pids(t_minishell *shell)
{
	t_pid_list	*current;
	int			ret;
	int			status;

	if (shell == NULL)
		return (EXIT_FAILURE);
	current = shell->pid_list;
	ret = EXIT_SUCCESS;
	while (current != NULL)
	{
		if (current->pid == PID_ERROR && current->next == NULL)
			ret = EXIT_FAILURE;
		else if (current->pid != PID_ERROR)
		{
			if (waitpid(current->pid, &status, 0) == -1)
				ret = EXIT_FAILURE;
			if (get_sigint())
			{
				kill_all_childs(shell->pid_list);
				break ;
			}
			if (ret == 0 && current->next == NULL && !WIFEXITED(status))
				ret = WEXITSTATUS(status);
			else if (ret == 0 && current->next == NULL && WEXITSTATUS(status))
				ret = WEXITSTATUS(status);
		}
		current = current->next;
	}
	pid_list_clear(&(shell->pid_list));
	return (ret);
}

/*
 *	Returns the shell's current status (by checking all the subprocess'
 *	execution status)
 *	If the shell's pid list is empty, the current shell's status is returned
 */
int	t_minishell_get_exec_status(t_minishell *shell)
{
	int		status;
	size_t	nb_pids;

	if (shell == NULL)
		return (EXIT_FAILURE);
	nb_pids = pid_list_size(shell->pid_list);
	if (nb_pids == 0)
		return (shell->status);
	set_interactive_mode(false);
	status = t_minishell_wait_pids(shell);
	shell->status = status;
	return (status);
}
