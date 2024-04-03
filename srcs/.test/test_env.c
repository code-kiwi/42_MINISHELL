/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:44:06 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/03 11:04:55 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	char		*value;

	t_minishell_init(&shell, argc, argv, envp);
	ft_lstprint(shell.env, env_element_print);
	value = env_get(shell.env, "_");
	if (value == NULL)
	{
		if (errno == 0)
			printf("Value not found but no error\n");
		else
			printf("Value not found, error: %s\n", strerror(errno));
	}
	else
	{
		printf("FOUND VALUE: \"%s\"\n", value);
	}
	t_minishell_free(&shell);
	return (0);
}
