/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:14:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/29 14:01:46 by mhotting         ###   ########.fr       */
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
		token_recognition(&shell);
		shell.ast = build_ast(shell.tokens);
		if (shell.ast == NULL)
			handle_error(&shell, ERROR_MSG_AST_CREATION, EXIT_FAILURE);
		exec_ast(&shell);
		ft_lstclear(&shell.tokens, t_token_free);
		ast_free(&(shell.ast));
		if (shell.fds_ast[0] != FD_ERROR && shell.fds_ast[0] != FD_UNSET)
			fd_close_and_reset(&(shell.fds_ast[0]));
		if (shell.fds_ast[1] != FD_ERROR && shell.fds_ast[1] != FD_UNSET)
			fd_close_and_reset(&(shell.fds_ast[1]));
		add_history(shell.input);
		free(shell.input);
		shell.input = NULL;
	}
	exit(EXIT_SUCCESS);
}
