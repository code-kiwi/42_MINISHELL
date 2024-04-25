/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:10:34 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/25 18:14:26 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "minishell.h"
#include "env.h"
#include "built_in.h"

int	bi_cd_handle_error(char *msg, int status, char *dir)
{
	if (dir == NULL)
		ft_dprintf(STDERR_FILENO, CD_MSG_LITERAL1, msg);
	else
		ft_dprintf(STDERR_FILENO, CD_MSG_LITERAL2, dir, msg);
	return (status);
}

static char	*bi_cd_resolve_path(t_minishell *shell, char *dir)
{
	char	*pwd;
	char	*path;

	if (shell == NULL || dir == NULL)
		return (NULL);
	pwd = env_get(shell->env, "PWD");
	if (pwd == NULL && errno != 0)
		return (NULL);
	if (pwd == NULL)
	{
		pwd = getcwd(NULL, 0);
		if (pwd == NULL)
			return (NULL);
	}
	path = bridge(pwd, "/", dir);
	free(pwd);
	return (path);
}

static char	*bi_cd_clean_path(char *path)
{
	char	*ptr;

	if (path == NULL)
		return (NULL);
	ptr = path;
	while (*ptr != '\0' && *(ptr + 1) != '\0')
	{
		if (*ptr == '.' && *(ptr + 1) == '/')
			ft_memmove(ptr, ptr + 2, ft_strlen(ptr + 2));
	}
	return (path);
}

static char	*bi_cd_get_path(t_minishell *shell, char *dir)
{
	char	*path;

	if (dir == NULL)
		return (NULL);
	if (dir[0] == '/')
		path = ft_strdup(dir);
	else
		path = bi_cd_resolve_path(shell, dir);
	bi_cd_clean_path(path);
	return (path);
}

int	bi_cd(t_minishell *shell, char **argv)
{
	char	*dir;
	char	*path;

	if (shell == NULL || argv == NULL || argv[0] == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	dir = argv[1];
	if (dir == NULL)
	{
		path = env_get(shell->env, "HOME");
		if (path == NULL)
			return (bi_cd_handle_error(CD_MSG_ERR_HOME, EXIT_FAILURE, NULL));
	}
	if (argv[2] != NULL)
		return (bi_cd_handle_error(CD_MSG_ERR_ARGS, EXIT_FAILURE, NULL));
	if (dir[0] == '\0')
		return (EXIT_SUCCESS);
	path = bi_cd_get_path(shell, dir);
	if (path == NULL && errno != 0)
		return (bi_cd_handle_error(CD_MSG_ERR_INTERNAL, EXIT_FAILURE, NULL));
	else if (path == NULL)
		return (bi_cd_handle_error(CD_MSG_ERR_EXISTS, EXIT_FAILURE, dir));
	return (bi_cd_execution(shell, path));
}
