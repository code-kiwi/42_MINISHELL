/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:14:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/23 22:01:00 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	t_minishell_init(&shell, argc, argv, envp);
	while (true)
	{
		shell.input = prompt(&shell);
		if (ft_strcmp(shell.input, "exit") == 0)
		{
			t_minishell_free(&shell);
			break ;
		}
		token_recognition(&shell);
		shell.ast = build_ast(shell.tokens);
		if (shell.ast == NULL)
			handle_error(&shell, ERROR_MSG_AST_CREATION, EXIT_FAILURE);
		exec_ast(&shell, NULL);
		ft_lstclear(&shell.tokens, t_token_free);
		ast_free(&(shell.ast));
		add_history(shell.input);
		free(shell.input);
		shell.input = NULL;
	}
	exit(EXIT_SUCCESS);
}
