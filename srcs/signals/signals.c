/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:06:42 by root              #+#    #+#             */
/*   Updated: 2024/05/01 10:01:59 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>

static volatile sig_atomic_t	g_code_received;

void	signal_handler(int code)
{
	if (code != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	if (g_code_received == INTERACTIVE
		|| g_code_received == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	g_code_received = SIGINT;
}

void	handle_interactive_signals(t_minishell *shell)
{
	if (g_code_received != SIGINT)
		return ;
	t_minishell_free(shell);
	exit(EXIT_SUCCESS);
	g_code_received = INTERACTIVE;
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

bool	get_sigint(void)
{
	return (g_code_received == SIGINT);
}
