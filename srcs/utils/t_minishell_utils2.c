/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:10:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/16 19:37:28 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	t_minishell_get_exec_status(t_minishell *shell)
{
	int		status;
	size_t	nb_pids;

	if (shell == NULL)
		return (EXIT_FAILURE);
	nb_pids = pid_list_size(shell->pid_list);
	if (nb_pids == 0)
		return (shell->status);
	status = t_minishell_wait_pids(shell);
	shell->status = status;
	return (status);
}
