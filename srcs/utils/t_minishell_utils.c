/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:10:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/03 14:36:36 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_minishell_init(t_minishell *shell)
{
	if (shell == NULL)
		return ;
	shell->input = NULL;
	shell->tokens = NULL;
}

void	t_minishell_free(t_minishell *shell)
{
	if (shell == NULL)
		return ;
	if (shell->input)
		free(shell->input);
	if (shell->tokens)
		ft_lstclear(&shell->tokens, t_token_free);
	rl_clear_history();
}
