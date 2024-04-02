/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:14:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/02 13:41:37 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TEMPORARY
#include "test.h"

int	main(void)
{
	t_minishell	shell;

	t_minishell_init(&shell);
	while (true)
	{
		shell.input = prompt();
		if (shell.input == NULL)
			handle_error(&shell, ERROR_MSG_PROMPT, EXIT_FAILURE);
		if (ft_strcmp(shell.input, "exit") == 0)
		{
			t_minishell_free(&shell);
			break ;
		}
		token_recognition(shell.input);
		printf("test\n");
		free(shell.input);
		shell.input = NULL;
	}
	exit(EXIT_SUCCESS);
}
