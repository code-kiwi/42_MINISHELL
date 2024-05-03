/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:02:08 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/03 13:05:35 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/readline.h>
#include <errno.h>
#include "libft.h"
#include "minishell.h"
#include "prompt.h"
#include "signals.h"

bool	interrupted(char *input)
{
	return (input == NULL && errno == 0);
}

/**
 * we read the input while it's being interrupted,
 * printf("\033[1A") allows us to go one line up in
 * 	the terminal because for some reason, when readline
 * is called 3 times and more, he adds a linebreak.
*/
static char	*read_input(char *prompt)
{
	char	*input;

	input = readline(prompt);
	while ((errno == EINTR || errno == 0) && catch_sigint())
	{
		errno = 0;
		free(input);
		input = readline(prompt);
	}
	return (input);
}

char	*prompt(t_minishell *shell)
{
	char	*input;
	char	cwd[CWD_BUFFER_SIZE];

	set_interactive_mode(true);
	if (isatty(STDIN_FILENO))
	{
		if (get_directory_path(cwd, CWD_BUFFER_SIZE) == false)
			ft_memcpy(cwd, "Minishell", 10);
		input = read_input(cwd);
	}
	else
		input = read_input(NULL);
	if (interrupted(input))
	{
		t_minishell_free(shell);
		exit(EXIT_SUCCESS);
	}
	if (input == NULL)
		handle_error(shell, ERROR_MSG_PROMPT, EXIT_FAILURE);
	return (input);
}
