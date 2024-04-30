/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:06:42 by root              #+#    #+#             */
/*   Updated: 2024/04/30 14:22:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>

int	g_code_received;

static void	signal_handler(int code)
{
	if (code == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (g_code_received == -1)
		g_code_received = code;
}

void	init_signals(void)
{
	g_code_received = -1;
	signal(SIGINT, &signal_handler);
}

void	handle_interactive_signals(t_minishell *shell)
{
	if (g_code_received != SIGINT)
		return ;
	t_minishell_free(shell);
	exit(EXIT_SUCCESS);
	g_code_received = -1;
}

bool	catch_sigint(void)
{
	if (g_code_received == SIGINT)
	{
		g_code_received = -1;
		return (true);
	}
	return (false);
}
