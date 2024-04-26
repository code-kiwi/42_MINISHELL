/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:10:14 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/26 14:17:09 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "env.h"

/*
 *	Deletes variables from the environment
 *	Each variables from argv[1+] are removed if they exist
 *	Returns EXIT_SUCCESS on SUCCESS, EXIT_FAILURE on ERROR
 */
int	bi_unset(t_minishell *shell, char **argv)
{
	size_t	i;

	if (shell == NULL || argv == NULL || argv[0] == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	i = 1;
	while (argv[i] != NULL)
	{
		env_delete(&(shell->env), argv[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
