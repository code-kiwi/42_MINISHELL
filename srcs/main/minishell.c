/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:14:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/03 12:48:34 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <errno.h>
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

	if (signal(SIGINT, &signal_handler) == SIG_ERR
		|| signal(SIGQUIT, &signal_handler) == SIG_ERR)
		exit(EXIT_FAILURE);
	rl_catch_signals = 0;
	rl_outstream = stderr;
	t_minishell_init(&shell, argc, argv, envp);
	rl_event_hook = stop_readline;
	while (true)
	{
		shell.input = prompt(&shell);
		if (shell.input == NULL)
			handle_error(&shell, ERROR_MSG_PROMPT, EXIT_FAILURE);
		token_recognition(&shell);
		shell.ast = build_ast(shell.tokens);
		if (shell.ast == NULL)
		{
			if (errno == 0)
			{
				utils_reset_shell(&shell);
				continue ;
			}
			handle_error(&shell, ERROR_MSG_AST_CREATION, EXIT_FAILURE);
		}
		exec_ast(&shell, NULL);
		printf("status : %d\n", shell.status);
		add_history(shell.input);
		utils_reset_shell(&shell);
	}
	exit(EXIT_SUCCESS);
}
