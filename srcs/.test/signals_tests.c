/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_tests.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:17:08 by brappo            #+#    #+#             */
/*   Updated: 2024/04/30 10:06:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "minishell.h"
#include "libft.h"

#define SIGNAL_HANDLER_ERROR "signal_handler is called uninitialized"
#define SIGACTION_ERROR "sigaction failed"

static void	signal_handler(int signal_code, siginfo_t *siginfo, void *context)
{
	static t_minishell	*shell = NULL;
	
	if (shell == NULL && siginfo == NULL && signal_code == -1)
	{
		shell = context;
		return ;
	}
	if (shell == NULL)
	{
		ft_printf("%s\n", SIGNAL_HANDLER_ERROR);
		exit(EXIT_FAILURE);
	}
	t_minishell_free(shell);
	exit(signal_code);
}

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
		exec_ast(&shell, NULL);
		ft_lstclear(&shell.tokens, t_token_free);
		ast_free(&(shell.ast));
		add_history(shell.input);
		free(shell.input);
		shell.input = NULL;
	}
	exit(EXIT_SUCCESS);
}
