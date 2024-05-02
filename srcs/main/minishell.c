/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:14:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/02 08:37:33 by root             ###   ########.fr       */
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
#include <stdio.h>

int	ft_getc(FILE *stream)
{
	char	c;

	if (stream == NULL)
		return (EOF);
	if (read(STDIN_FILENO, &c, 1) == -1)
		return (EOF);
	return (c);
}

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
		token_recognition(&shell);
		shell.ast = build_ast(shell.tokens);
		if (shell.ast == NULL)
			handle_error(&shell, ERROR_MSG_AST_CREATION, EXIT_FAILURE);
		exec_ast(&shell, NULL);
		ft_printf("status : %d\n", shell.status);
		ft_lstclear(&shell.tokens, t_token_free);
		ast_free(&(shell.ast));
		add_history(shell.input);
		free(shell.input);
		shell.input = NULL;
	}
	exit(EXIT_SUCCESS);
}
