/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_get_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:53:09 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/14 10:50:23 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

#include "libft.h"
#include "minishell.h"
#include "env.h"

/*
 *	Returns true if the given path is valid, else returns false
 *	If the path does not exist, status is set to STATUS_CMD_NOT_FOUND, if it
 *	exists but is not authorized, status is set to STATUS_CMD_NOT_EXEC
*/
static bool	is_valid_cmd_path(char *path, int *status)
{
	if (path_is_dir(path) || access(path, F_OK) != 0)
	{
		*status = STATUS_CMD_NOT_FOUND;
		return (false);
	}
	else if (access(path, F_OK | X_OK) != 0)
	{
		*status = STATUS_CMD_NOT_EXEC;
		return (false);
	}
	*status = 0;
	return (true);
}

/*
 *	Returns the path to a given command
 *	Uses the paths array to test each possible path to the given command
 *	As soon as one valid path is found (existing and executable file), it
 *	is returned
 *	If no path was found or if an error occurred, returns NULL
 *	If the given command contains a slash, returns a duplicate of given_cmd if
 *	given_cmd exists and corresponds to an executable file
 *	NB: status is set to the appropriate value thanks to the call to
 *	is_valid_path() function. If the status is STATUS_CMD_NOT_EXEC, it means
 *	that a command has been found but is not executable, then path is returned
 */
static char	*get_command_path(char **paths, char *given_cmd, int *status)
{
	size_t	i;
	char	*full_path;

	if (paths == NULL || given_cmd == NULL)
		return (NULL);
	if (ft_strchr(given_cmd, '/') != NULL)
	{
		if (is_valid_cmd_path(given_cmd, status)
			|| *status == STATUS_CMD_NOT_EXEC)
			return (ft_strdup(given_cmd));
		return (NULL);
	}
	i = 0;
	while (paths[i] != NULL)
	{
		full_path = ft_strjoin(paths[i], given_cmd);
		if (full_path == NULL)
			return (NULL);
		if (is_valid_cmd_path(full_path, status)
			|| *status == STATUS_CMD_NOT_EXEC)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

/*
 *	Adds all the possible paths to the given res NULL terminated array
 *	Use ft_strtok() in order to get all the paths within a loop, then adds
 *	a '/' character at the end of each one before adding it to res
 *	Returns true on SUCCESS, false on ERROR
 */
static bool	split_env(char *path_str, char **res, size_t nb_paths)
{
	size_t	i;
	char	*path_token;
	char	*temp;

	if (path_str == NULL || res == NULL)
		return (false);
	i = 0;
	path_token = ft_strtok(path_str, PATH_STR_SEPERATOR);
	while (i < nb_paths && path_token != NULL)
	{
		if (*path_token != '\0')
		{
			temp = ft_append_chars(path_token, '/', ft_strlen(path_token) + 1);
			if (temp == NULL)
				return (false);
			res[i] = temp;
			i++;
		}
		path_token = ft_strtok(NULL, PATH_STR_SEPERATOR);
	}
	return (true);
}

/*
 *	Returns a NULL terminated array of all the paths saved into the
 *	shell's env PATH
 *	If there is no PATH into shells'env, returns an empty array
 *	In case of ERROR, returns NULL
 */
char	**get_all_paths(t_minishell *shell)
{
	char	*raw_path;
	size_t	nb_paths;
	char	**res;

	if (shell == NULL)
		return (NULL);
	raw_path = env_get(shell->env, ENV_PATH);
	if (raw_path == NULL && errno == 0)
		return (ft_split("", ""));
	else if (raw_path == NULL)
		return (NULL);
	nb_paths = ft_count_words(raw_path, PATH_STR_SEPERATOR);
	res = (char **) ft_calloc((nb_paths + 1), sizeof(char *));
	if (res == NULL || !split_env(raw_path, res, nb_paths))
	{
		free(raw_path);
		ft_free_str_array(&res);
		return (NULL);
	}
	free(raw_path);
	return (res);
}

/*
 *	Returns the valid path to a given command name
 *	If the command's name contains a slash, then is is just duplicated (if the
 *	given command exists and corresponds to an executable file)
 *	Else:
 *		- we retrieve the PATH envrionment variable from the given shell
 *		- we test all the paths from path in order to find an existing
 *		and executable path to our command
 *		- we return a path to the command (allocated string)
 *		- the status given is set to the right value: 0 if ok,
 *		STATUS_CMD_NOT_FOUND if not found, STATUS_CMD_NOT_EXEC if found but
 *		not authorized
 *	In case of ERROR, returns NULL
 *	Error cases:
 *		- internal problem (memory allocation failed)
 *		- no path to the command has been found
 *	NB: if the command was found but is not authorized, we return the path
 *	to the command found as an allocated string
 */
char	*exec_cmd_get_path(t_minishell *shell, char *cmd, int *status)
{
	char	**paths;
	char	*cmd_path;

	if (shell == NULL || cmd == NULL)
		return (NULL);
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (path_is_dir(cmd))
		{
			*status = STATUS_CMD_NOT_EXEC;
			return (ft_strdup(cmd));
		}
		if (is_valid_cmd_path(cmd, status) || *status == STATUS_CMD_NOT_EXEC)
			return (ft_strdup(cmd));
		return (NULL);
	}
	paths = get_all_paths(shell);
	if (paths == NULL)
		return (NULL);
	cmd_path = get_command_path(paths, cmd, status);
	ft_free_str_array(&paths);
	return (cmd_path);
}
