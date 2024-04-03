/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:10:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/03 02:34:36 by mhotting         ###   ########.fr       */
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
}

void	t_minishell_free(t_minishell *shell)
{
	if (shell == NULL)
		return ;
	if (shell->input)
		free(shell->input);
	if (shell->env != NULL)
		ft_lstclear(&(shell->env), env_element_free);
}
