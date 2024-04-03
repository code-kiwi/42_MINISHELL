/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:02:08 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/03 15:54:44 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(t_minishell *shell)
{
	char	*input;
	char	cwd[CWD_BUFFER_SIZE];

	get_directory_path(cwd, shell, CWD_BUFFER_SIZE);
	rl_redisplay();
	input = readline(cwd);
	if (input == NULL)
		handle_error(shell, ERROR_MSG_PROMPT, EXIT_FAILURE);
	return (input);
}
