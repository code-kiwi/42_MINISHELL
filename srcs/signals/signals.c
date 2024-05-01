/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:06:42 by root              #+#    #+#             */
/*   Updated: 2024/05/01 10:27:08 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>

static volatile sig_atomic_t	g_code_received;

void	set_interactive_mode(bool interactive)
{
	if (interactive)
		g_code_received = INTERACTIVE;
	else
		g_code_received = NON_INTERACTIVE;
}

void	signal_handler(int code)
{
	bool	error;

	if (code != SIGINT)
		return ;
	error = (write(STDOUT_FILENO, "\n", 1) == -1);
	if (g_code_received == INTERACTIVE
		|| g_code_received == SIGINT)
	{
		error = (rl_on_new_line() == -1) || error;
		rl_replace_line("", 1);
		rl_redisplay();
	}
	g_code_received = SIGINT;
	if (error)
		g_code_received = ERROR_SIGNAL;
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

bool	get_sigint(void)
{
	return (g_code_received == SIGINT);
}

bool	get_signal_error(void)
{
	return (g_code_received == ERROR_SIGNAL);
}
