/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:02:08 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/01 13:56:22 by root             ###   ########.fr       */
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

char	*prompt(t_minishell *shell)
{
	char	*input;
	char	cwd[CWD_BUFFER_SIZE];

	if (get_directory_path(cwd, CWD_BUFFER_SIZE) == false)
		ft_memcpy(cwd, "Minishell", 10);
	set_interactive_mode(true);
	input = readline(cwd);
	if (input == NULL)
	{
		if (errno == 0)
		{
			t_minishell_free(shell);
			exit(EXIT_SUCCESS);
		}
		handle_error(shell, ERROR_MSG_PROMPT, EXIT_FAILURE);
	}
	if (catch_sigint())
		shell->status = 130;
	if (get_signal_error())
		handle_error(shell, SIGNAL_ERROR, EXIT_FAILURE);
	return (input);
}
