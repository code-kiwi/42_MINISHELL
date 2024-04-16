/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:10:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/16 20:18:31 by mhotting         ###   ########.fr       */
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
	shell->is_child_process = false;
	shell->status = 0;
}

void	t_minishell_free(t_minishell *shell)
{
	rl_clear_history();
	if (shell == NULL)
		return ;
	if (shell->parent != NULL)
		t_minishell_free(shell->parent);
	if (shell->input)
		free(shell->input);
	rl_clear_history();
	if (shell->env != NULL)
		ft_lstclear(&(shell->env), env_element_free);
	if (shell->tokens)
		ft_lstclear(&shell->tokens, t_token_free);
	if (shell->pid_list != NULL)
	{
		if (shell->is_child_process)
			pid_list_clear(&(shell->pid_list));
		else
			t_minishell_get_exec_status(shell);
	}
	if (shell->ast != NULL)
		ast_free(&(shell->ast));
}

void	t_minishell_init_subshell(t_minishell *sub, t_minishell *parent)
{
	if (sub == NULL || parent == NULL)
		return ;
	t_minishell_init(sub, 0, NULL, NULL);
	sub->env = parent->env;
	parent->env = NULL;
	sub->parent = parent;
}
