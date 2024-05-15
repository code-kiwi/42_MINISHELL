/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:11:12 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/15 15:16:13 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include "libft.h"
#include "minishell.h"
#include "env.h"

/*
 *	Returns true if the given key is valid, otherwise returns false
 */
static bool	bi_export_is_valid_key(char *key)
{
	size_t	i;

	if (key == NULL)
		return (false);
	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (false);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

/*
 *	Returns true if the key extracted from key_val is valid, otherwise returns
 *	false
 *	When the key is invalid, an error message is printed
 *	In case of ERROR, returns false
 */
static bool	bi_export_has_valid_key(char *key_val)
{
	size_t	i;
	char	*key;
	bool	is_valid;

	i = 0;
	if (key_val == NULL)
		return (false);
	while (key_val[i] != '\0' && key_val[i] != '=')
		i++;
	if (key_val[i] == '=')
		key = ft_substr(key_val, 0, i);
	else
		key = ft_strdup(key_val);
	if (key == NULL)
		return (false);
	is_valid = bi_export_is_valid_key(key);
	if (!is_valid)
		ft_dprintf(STDERR_FILENO, EXPORT_MSG_ERR_KEY, key);
	free(key);
	return (is_valid);
}

/*
 *	Given a key_val string, adds the key/value pair into the given shell's
 *	environment
 *	Returns 0 on SUCCESS, 1 on ERROR
 */
static int	bi_export_var(t_minishell *shell, char *key_val)
{
	char	**split;
	bool	returned;

	if (!bi_export_has_valid_key(key_val))
		return (1);
	split = ft_split_key_val(key_val, ENV_KEY_VALUE_SEPERATOR);
	if (split == NULL && errno != 0 && errno != EINVAL)
		return (1);
	if (split == NULL || split[0] == NULL || split[1] == NULL)
	{
		errno = 0;
		ft_free_str_array(&split);
		return (0);
	}
	returned = env_update(&(shell->env), split[0], split[1], false);
	ft_free_str_array(&split);
	if (!returned)
		return (1);
	return (0);
}

/*
 *	Sets variables into the given shell's environment
 *	The expected strings into argv are: "KEY=VALUE"
 *	Multiple keys can be assigned in one call
 *	Returns EXIT_SUCCESS on SUCCESS, EXIT_FAILURE on ERROR
 */
int	bi_export(t_minishell *shell, char **argv, int fd_out)
{
	size_t	i;
	int		returned;

	if (shell == NULL || argv == NULL || argv[0] == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	(void) fd_out;
	returned = 0;
	i = 1;
	while (argv[i] != NULL)
	{
		returned += bi_export_var(shell, argv[i]);
		i++;
	}
	if (returned != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
