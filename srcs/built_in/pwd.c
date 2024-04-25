/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:10:53 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/25 14:09:51 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "minishell.h"
#include "env.h"
#include "built_in.h"

/*
 *	Prints the  name of current/working directory
 *	Uses the environment variable PWD if it exists
 *	Else calls the function getcwd()
 *	Returns EXIT_SUCCESS on SUCCESS, EXIT_FAILURE on ERROR
 */
int	bi_pwd(t_minishell *shell, char **argv)
{
	char	*curr_dir;

	if (shell == NULL || argv == NULL || argv[0] == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	curr_dir = env_get(shell->env, "PWD");
	if (curr_dir == NULL && errno != 0)
	{
		ft_dprintf(STDERR_FILENO, MSG_LITERAL, PWD_MSG_ERROR);
		return (EXIT_FAILURE);
	}
	if (curr_dir == NULL)
	{
		curr_dir = getcwd(NULL, 0);
		if (curr_dir == NULL)
		{
			ft_dprintf(STDERR_FILENO, MSG_LITERAL, PWD_MSG_ERROR);
			return (EXIT_FAILURE);
		}
	}
	ft_printf(MSG_LITERAL, curr_dir);
	free(curr_dir);
	return (EXIT_SUCCESS);
}
