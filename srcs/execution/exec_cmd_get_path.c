/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_get_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:53:09 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/14 12:17:07 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_command_path(char **paths, char *given_cmd)
{
	size_t	i;
	char	*full_path;

	if (paths == NULL || given_cmd == NULL)
		return (NULL);
	if (ft_strchr(given_cmd, '/') != NULL)
		return (ft_strdup(given_cmd));
	i = 0;
	while (paths[i] != NULL)
	{
		full_path = ft_strjoin(paths[i], given_cmd);
		if (full_path == NULL)
			return (NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

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
		temp = ft_append_chars(path_token, '/', ft_strlen(path_token) + 1);
		if (temp == NULL)
			return (false);
		res[i] = temp;
		path_token = ft_strtok(NULL, PATH_STR_SEPERATOR);
		i++;
	}
	return (true);
}

char	**get_all_paths(t_minishell *shell)
{
	char	*raw_path;
	size_t	nb_paths;
	char	**res;

	if (shell == NULL)
		return (NULL);
	raw_path = env_get(shell->env, "PATH");
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

char	*exec_cmd_get_path(t_minishell *shell, char *cmd)
{
	char	**paths;
	char	*cmd_path;

	if (shell == NULL || cmd == NULL)
		return (NULL);
	paths = get_all_paths(shell);
	if (paths == NULL)
		return (NULL);
	cmd_path = get_command_path(paths, cmd);
	ft_free_str_array(&paths);
	return (cmd_path);
}
