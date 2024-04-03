/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:14:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/03 10:05:09 by brappo           ###   ########.fr       */
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
		shell.tokens = token_recognition(shell.input);
		if (shell.tokens == NULL)
			handle_error(&shell, TOKENIZATION_ERROR, EXIT_FAILURE);
		ft_lstprint(shell.tokens, print_token);
		ft_lstclear(&shell.tokens, t_token_free);
		free(shell.input);
		shell.input = NULL;
	}
	exit(EXIT_SUCCESS);
}
