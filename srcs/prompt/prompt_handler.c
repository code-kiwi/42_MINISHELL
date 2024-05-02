/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:02:08 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/02 09:22:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/readline.h>
#include "minishell.h"
#include "prompt.h"
#include "signals.h"
#include <signal.h>
#include <errno.h>
#include "libft.h"

static bool	interrupted(char *input)
{
	return (input == NULL && errno == 0);
}

static char	*read_input(char *prompt)
{
	char	*input;
	bool	first_sigint;

	first_sigint = true;
	input = readline(prompt);
	while (interrupted(input) && catch_sigint())
	{
		if (!first_sigint)
			printf("\033[1A");
		input = readline(prompt);
		first_sigint = false;
	}
	return (input);
}

char	*prompt(t_minishell *shell)
{
	char	*input;
	char	cwd[CWD_BUFFER_SIZE];

	if (get_directory_path(cwd, CWD_BUFFER_SIZE) == false)
		ft_memcpy(cwd, "Minishell", 10);
	set_interactive_mode(true);
	input = read_input(cwd);
	if (interrupted(input))
	{
		t_minishell_free(shell);
		exit(EXIT_SUCCESS);
	}
	if (input == NULL)
		handle_error(shell, ERROR_MSG_PROMPT, EXIT_FAILURE);
	return (input);
}
