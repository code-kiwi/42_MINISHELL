/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:10:34 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/15 15:14:46 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

#include "libft.h"
#include "minishell.h"
#include "env.h"
#include "built_in.h"

/*
 *	Handles cd built_in errors
 *	Displays the appropriate error message and returns the given status
 */
int	bi_cd_handle_error(char *msg, int status, char *dir)
{
	if (dir == NULL)
		ft_dprintf(STDERR_FILENO, CD_MSG_LITERAL1, msg);
	else
		ft_dprintf(STDERR_FILENO, CD_MSG_LITERAL2, dir, msg);
	return (status);
}

/*
 *	Returns the concatenation of the current working directory and the given
 *	directory, seperated by a '/' char
 *	The current working directory is retrieved into the PWD env. variable, but
 *	if it does not exist, a call to getcwd() is performed
 *	In case of ERROR, returns NULL
 */
static char	*bi_cd_resolve_path(t_minishell *shell, char *dir)
{
	char	*pwd;
	char	*path;

	if (shell == NULL || dir == NULL)
		return (NULL);
	pwd = env_get(shell->env, ENV_PWD);
	if (pwd == NULL && errno != 0)
		return (NULL);
	if (pwd == NULL)
	{
		pwd = getcwd(NULL, 0);
		if (pwd == NULL)
			return (NULL);
		if (!env_update(&(shell->env), ENV_PWD, pwd, false))
		{
			free(pwd);
			return (NULL);
		}
	}
	path = bridge(pwd, dir, "/");
	free(pwd);
	return (path);
}

/*
 *	Given a directory, returns a duplicate of itself if it corresponds to an
 *	absolute path, else returns the concatenation of the current working
 *	directory and the given directory (seperated by a '/' char)
 *	In case of ERROR, returns NULL
 */
static char	*bi_cd_get_path(t_minishell *shell, char *dir)
{
	char	*path;

	if (dir == NULL)
		return (NULL);
	if (dir[0] == '/')
		path = ft_strdup(dir);
	else
		path = bi_cd_resolve_path(shell, dir);
	return (path);
}

/*
 *	Changes the working directory
 *	Cases:
 *		- if no argument is given, tries to reach the directory stored into the
 *		HOME environment variable (if it does not exist, prompts an error)
 *		- if multiple arguments are given, prompts an error
 *		- if the first argument is empty, nothing happens
 *		- else, if the argument starts with '/', it is considered as an
 *		absolute path, if it starts with anything else, the path reached is
 *		the concatenation of the current working directory and the argument
 *	Updates the environment variables OLDPWD and PWD
 *	Returns EXIT_SUCCESS on SUCCESS, EXIT_FAILURE on ERROR
 */
int	bi_cd(t_minishell *shell, char **argv, int fd_out)
{
	char	*dir;
	char	*path;
	int		status;

	if (shell == NULL || argv == NULL || argv[0] == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	(void) fd_out;
	dir = argv[1];
	if (dir == NULL)
	{
		path = env_get(shell->env, "HOME");
		if (path == NULL)
			return (bi_cd_handle_error(CD_MSG_ERR_HOME, EXIT_FAILURE, NULL));
	}
	else if (argv[2] != NULL)
		return (bi_cd_handle_error(CD_MSG_ERR_ARGS, EXIT_FAILURE, NULL));
	else if (dir[0] == '\0')
		return (EXIT_SUCCESS);
	else
		path = bi_cd_get_path(shell, dir);
	if (path == NULL)
		return (bi_cd_handle_error(CD_MSG_ERR_INTERNAL, EXIT_FAILURE, NULL));
	status = bi_cd_execution(shell, path);
	free(path);
	return (status);
}
