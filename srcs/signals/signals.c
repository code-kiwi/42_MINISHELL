/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:06:42 by root              #+#    #+#             */
/*   Updated: 2024/04/30 14:02:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>

int	code_received;

static void	signal_handler(int code)
{
	if (code == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (code_received == -1)
		code_received = code;
}

void	init_signals()
{
	code_received = -1;
	signal(SIGINT, &signal_handler);
}

void	handle_interactive_signals(t_minishell *shell)
{
	if (code_received != SIGINT)
		return ;
	t_minishell_free(shell);
	exit(EXIT_SUCCESS);
	code_received = -1;
}

bool	catch_sigint()
{
	if (code_received == SIGINT)
	{
		code_received = -1;
		return (true);
	}
	return (false);
}

