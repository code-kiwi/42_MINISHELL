/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:14:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/05 21:27:54 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include "minishell.h"
#include "prompt.h"
#include "libft.h"
#include "token.h"
#include "node.h"
#include "build_ast.h"
#include "execution.h"
#include "signals.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	if (signal(SIGINT, &signal_handler) == SIG_ERR)
		exit(EXIT_FAILURE);
	t_minishell_init(&shell, argc, argv, envp);
	rl_getc_function = ft_getc;
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
		if (!exec_ast_heredocs(&shell))
			handle_error(&shell, ERROR_MSG_HEREDOC_EXEC, EXIT_FAILURE);
		if (shell.heredoc_interruption)
		{
			utils_reset_shell(&shell);
			shell.status = STATUS_SIGINT_STOP;
			continue ;
		}
		exec_ast(&shell, NULL);
		add_history(shell.input);
		utils_reset_shell(&shell);
	}
	exit(EXIT_SUCCESS);
}
