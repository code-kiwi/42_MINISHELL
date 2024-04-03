/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:44:06 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/03 14:39:26 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_env_find(t_list *env, char *name)
{
	char	*value;

	if (env == NULL || name == NULL)
		return ;
	value = env_get(env, name);
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
	env_add(&(shell.env), "PATH", "/usr/bin");
	env_add(&(shell.env), "USER", "brappo");
	ft_lstprint(shell.env, env_element_print);
	test_env_find(shell.env, "PATH");
	env_delete(&(shell.env), "USER");
	env_delete(&(shell.env), "PATH");
	env_delete(&(shell.env), "PATH");
	ft_lstprint(shell.env, env_element_print);
	printf("ENV: %p\n", shell.env);
	t_minishell_free(&shell);
	return (0);
}
