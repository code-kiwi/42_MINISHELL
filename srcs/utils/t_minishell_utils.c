/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:10:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/10 16:46:58 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_minishell_init(t_minishell *shell, int argc, char **argv, char **envp)
{
	if (shell == NULL)
		return ;
	ft_memset(shell, 0, sizeof(t_minishell));
	shell->env = env_extract(envp);
	(void)argc;
	(void)argv;
	shell->input = NULL;
	shell->tokens = NULL;
	shell->pid_list = NULL;
}

void	t_minishell_free(t_minishell *shell)
{
	rl_clear_history();
	if (shell == NULL)
		return ;
	if (shell->input)
		free(shell->input);
	rl_clear_history();
	if (shell->env != NULL)
		ft_lstclear(&(shell->env), env_element_free);
	if (shell->tokens)
		ft_lstclear(&shell->tokens, t_token_free);
	if (shell->pid_list != NULL)
		t_minishell_wait_pids(shell);
}

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

int	t_minishell_wait_pids(t_minishell *shell)
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
