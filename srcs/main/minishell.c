/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:14:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/01 18:51:12 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <readline/history.h>
#include "minishell.h"
#include "prompt.h"
#include "libft.h"
#include "token.h"
#include "node.h"
#include "build_ast.h"
#include "execution.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	t_minishell_init(&shell, argc, argv, envp);
	while (true)
	{
		shell.input = prompt(&shell);
		if (shell.input == NULL)
			handle_error(&shell, ERROR_MSG_PROMPT, EXIT_FAILURE);
		if (utils_is_empty_cmd(shell.input))
		{
			utils_handle_empty_cmd(&shell);
			continue ;
		}
		token_recognition(&shell);
		shell.ast = build_ast(shell.tokens);
		if (shell.ast == NULL)
			handle_error(&shell, ERROR_MSG_AST_CREATION, EXIT_FAILURE);
		exec_ast(&shell, NULL);
		add_history(shell.input);
		utils_reset_shell(&shell);
	}
	exit(EXIT_SUCCESS);
}
