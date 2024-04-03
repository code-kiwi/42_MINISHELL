/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:44:06 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/03 13:04:19 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_env_find(t_list *env, char *name)
{
	char	*value;

	if (env == NULL || name == NULL)
		return ;
	value = env_get(env, "_");
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
		free(value);
	}
}	

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	t_minishell_init(&shell, argc, argv, envp);
	ft_lstprint(shell.env, env_element_print);
	test_env_find(shell.env, "PATH");
	env_delete(&(shell.env), "PATH");
	test_env_find(shell.env, "PATH");
	t_minishell_free(&shell);
	return (0);
}
