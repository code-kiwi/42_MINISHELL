/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:10:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/17 11:35:01 by brappo           ###   ########.fr       */
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
	if (shell->tokens != NULL)
		ft_lstclear(&shell->tokens, t_token_free);
}
