/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:10:34 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/15 15:15:15 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>

#include "minishell.h"
#include "env.h"
#include "built_in.h"

/*
 *	Updates the environment variables OLDPWD and PWD
 *	OLDPWD is set using the PWD env value before updating is (if there was no
 *	PWD value stored in the env, cwd is used to set OLDPWD)
 *	PWD is set using the given cwd
 *	Returns EXIT_SUCCESS on SUCCESS, EXIT_FAILURE on ERROR
 */
static int	bi_cd_update_env(t_minishell *shell, char *cwd)
{
	char	*oldpwd;
	bool	ret;

	if (shell == NULL || cwd == NULL)
		return (EXIT_FAILURE);
	oldpwd = env_get(shell->env, ENV_PWD);
	if (oldpwd == NULL && errno != 0)
		return (EXIT_FAILURE);
	if (oldpwd == NULL)
		ret = env_update(&(shell->env), ENV_OLDPWD, cwd, false);
	else
	{
		ret = env_update(&(shell->env), ENV_OLDPWD, oldpwd, false);
		free(oldpwd);
	}
	ret = ret && env_update(&(shell->env), ENV_PWD, cwd, false);
	if (!ret)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
 *	Changes the working directory calling chdir() function with the given path
 *	Updates the environment variables OLDPWD and PWD
 *	Returns EXIT_SUCCESS on SUCCESS, EXIT_FAILURE on ERROR
 */
int	bi_cd_execution(t_minishell *shell, char *path)
{
	int		status;
	char	*cwd;

	if (shell == NULL || path == NULL)
		return (bi_cd_handle_error(CD_MSG_ERR_INTERNAL, EXIT_FAILURE, NULL));
	if (chdir(path) == -1)
		return (bi_cd_handle_error(CD_MSG_ERR_EXISTS, EXIT_FAILURE, path));
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (bi_cd_handle_error(CD_MSG_ERR_INTERNAL, EXIT_FAILURE, NULL));
	status = bi_cd_update_env(shell, cwd);
	free(cwd);
	return (status);
}
