/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:10:53 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/10 16:56:46 by mhotting         ###   ########.fr       */
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
int	bi_pwd(t_minishell *shell, char **argv, int fd_out)
{
	char	*curr_dir;
	int		ret;

	if (shell == NULL || argv == NULL || argv[0] == NULL || !is_fd_ok(fd_out))
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	curr_dir = env_get(shell->env, ENV_PWD);
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
	ret = ft_dprintf(fd_out, MSG_LITERAL, curr_dir);
	free(curr_dir);
	if (ret == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
