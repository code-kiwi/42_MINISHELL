/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:10:14 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/10 16:56:51 by mhotting         ###   ########.fr       */
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
int	bi_unset(t_minishell *shell, char **argv, int fd_out)
{
	size_t	i;

	if (shell == NULL || argv == NULL || argv[0] == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	(void) fd_out;
	i = 1;
	while (argv[i] != NULL)
	{
		env_delete(&(shell->env), argv[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
