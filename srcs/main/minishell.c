/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:14:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/30 18:55:47 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <readline/history.h>
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
