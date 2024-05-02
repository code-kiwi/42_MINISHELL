/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:02:08 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/02 08:37:15 by root             ###   ########.fr       */
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

static char	*read_input(char *prompt)
{
	char	*input;

	input = readline(prompt);
	if (input == NULL && errno == 0)
		input = readline(prompt);
	while (input == NULL && errno == 0)
	{
		printf("\033[1A");
		input = readline(prompt);
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
	if (input == NULL)
		handle_error(shell, ERROR_MSG_PROMPT, EXIT_FAILURE);
	if (catch_sigint())
		shell->status = 130;
	return (input);
}
