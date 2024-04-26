/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:11:37 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/26 12:53:07 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "built_in.h"
#include "env.h"

/*
 *	Prints the environment content
 *	In case of ERROR, prints an appropriate error message
 *	Returns EXIT_SUCCESS on SUCCESS, EXIT_FAILURE on ERROR
 */
int	bi_env(t_minishell *shell, char **argv)
{
	char	**env;
	size_t	i;

	if (shell == NULL || argv == NULL || argv[0] == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	if (argv[1] != NULL)
	{
		ft_dprintf(STDERR_FILENO, ENV_MSG_ERR_ARG);
		return (EXIT_FAILURE);
	}
	env = env_get_all_array(shell->env);
	if (env == NULL)
	{
		ft_dprintf(STDERR_FILENO, ENV_MSG_ERR_INTERNAL);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (env[i] != NULL)
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
	ft_free_str_array(&env);
	return (EXIT_SUCCESS);
}
