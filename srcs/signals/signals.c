/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:06:42 by root              #+#    #+#             */
/*   Updated: 2024/05/02 09:09:28 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include "prompt.h"
#include "libft.h"

static volatile sig_atomic_t	g_code_received;

/**
 * There's 2 mode for signals : interactive and non-interactive
 * 	interactive mode is when the user types input
 *  non-interactive is during the program execution
 * 
*/
void	set_interactive_mode(bool interactive)
{
	if (interactive)
		g_code_received = INTERACTIVE;
	else
		g_code_received = NON_INTERACTIVE;
}

/**
 * if ctrl + c is received during the interactive mode,
 * 		we just display a new prompt
 * otherwise, we set the value of code_received and
 * 		the code will test if code_received corresponds to SIGINT.
*/

void	signal_handler(int code)
{
	if (code != SIGINT)
		return ;
	g_code_received = SIGINT;
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
