/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:14:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/12 18:37:31 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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

static void	project_init(t_minishell *shell, int argc, char **argv, char **envp)
{
	if (
		signal(SIGINT, &signal_handler) == SIG_ERR
		|| signal(SIGQUIT, &signal_handler) == SIG_ERR
	)
	{
		ft_dprintf(STDERR_FILENO, "%s\n", ERROR_MSG_SIGNAL_INIT);
		exit(EXIT_FAILURE);
	}
	rl_catch_signals = 0;
	rl_outstream = stderr;
	rl_event_hook = stop_readline;
	t_minishell_init(shell, argc, argv, envp);
}

static int	project_main_loop(t_minishell *shell)
{
	shell->input = prompt(shell);
	if (shell->input == NULL)
		handle_error(shell, ERROR_MSG_PROMPT, EXIT_FAILURE);
	if (string_contains_invalid_chars(shell->input))
	{
		handle_error(NULL, ERROR_MSG_BAD_CHARS, 0);
		return (STATUS_INVALID_USE);
	}
	token_recognition(shell);
	shell->ast = build_ast(shell->tokens);
	if (shell->ast == NULL && errno != 0)
		handle_error(shell, ERROR_MSG_AST_CREATION, EXIT_FAILURE);
	else if (shell->ast == NULL)
		return (STATUS_INVALID_USE);
	if (!exec_ast_heredocs(shell))
		handle_error(shell, ERROR_MSG_HEREDOC_EXEC, EXIT_FAILURE);
	if (shell->heredoc_interruption)
		return (STATUS_SIGINT_STOP);
	exec_ast(shell, NULL);
	return (shell->status);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	int			status;

	project_init(&shell, argc, argv, envp);
	while (true)
	{
		status = project_main_loop(&shell);
		utils_reset_shell(&shell, status);
	}
	t_minishell_free(&shell);
	exit(EXIT_SUCCESS);
}
