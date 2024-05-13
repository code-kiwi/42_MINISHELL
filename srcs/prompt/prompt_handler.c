/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:02:08 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/13 22:05:59 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <errno.h>

#include "libft.h"
#include "minishell.h"
#include "prompt.h"
#include "signals.h"

bool	interrupted(char *input)
{
	return (input == NULL && (errno == 0 || errno == EINTR));
}

static char	*read_input(char *prompt, t_minishell *shell)
{
	char	*input;

	input = read_one_line(prompt);
	while ((errno == EINTR || errno == 0) && get_sigint())
	{
		set_interactive_mode(true);
		shell->status = 130;
		errno = 0;
		free(input);
		input = read_one_line(prompt);
	}
	return (input);
}

char	*prompt(t_minishell *shell)
{
	char	*input;
	char	cwd[CWD_BUFFER_SIZE];

	set_interactive_mode(true);
	if (shell->is_a_tty)
	{
		if (get_directory_path(shell->env, cwd, CWD_BUFFER_SIZE) == false)
			ft_memcpy(cwd, "Minishell", 10);
		input = read_input(cwd, shell);
	}
	else
		input = readline_not_tty();
	if (interrupted(input))
	{
		t_minishell_free(shell);
		exit(EXIT_SUCCESS);
	}
	if (input == NULL)
		handle_error(shell, ERROR_MSG_PROMPT, EXIT_FAILURE);
	return (input);
}
