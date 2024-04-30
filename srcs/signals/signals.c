/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:06:42 by root              #+#    #+#             */
/*   Updated: 2024/04/30 17:47:40 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>

static int	g_code_received;

static void	signal_handler(int code)
{
	if (code != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	if (g_code_received == INTERACTIVE)
	{
		if (code == SIGINT)
		{
			rl_on_new_line();
			rl_replace_line("", 1);
			rl_redisplay();
		}
	}
	else if (g_code_received == NON_INTERACTIVE)
		g_code_received = code;
}

void	init_signals(void)
{
	set_interactive_mode(true);
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
		g_code_received = INTERACTIVE;
		return (true);
	}
	return (false);
}

void	set_interactive_mode(bool interactive)
{
	if (interactive)
		g_code_received = INTERACTIVE;
	else
		g_code_received = NON_INTERACTIVE;
}
