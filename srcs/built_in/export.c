/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:11:12 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/16 12:28:15 by mhotting         ###   ########.fr       */
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

	if (key == NULL || *key == '\0')
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

static char	*bi_export_get_key(char *key_val)
{
	char	*key_eq_pos;
	char	*key_append_pos;

	if (key_val == NULL)
		return (NULL);
	key_eq_pos = ft_strstr(key_val, ENV_KEY_VALUE_SEPERATOR_STR);
	key_append_pos = ft_strstr(key_val, ENV_KEY_VALUE_SEPERATOR_APPEND_STR);
	if (key_eq_pos == NULL && key_append_pos == NULL)
		return (NULL);
	if (
		(key_eq_pos != NULL && key_append_pos == NULL)
		|| (key_eq_pos != NULL && key_eq_pos < key_append_pos)
	)
		return (ENV_KEY_VALUE_SEPERATOR_STR);
	return (ENV_KEY_VALUE_SEPERATOR_APPEND_STR);
}

/*
 *	Given a key_val string, adds the key/value pair into the given shell's
 *	environment
 *	Depending on the key found, will set a var into the env or update it
 *	Returns 0 on SUCCESS, 1 on ERROR
 */
static int	bi_export_var(t_minishell *shell, char *key_val)
{
	char	**split;
	bool	returned;
	char	*key_sep;

	key_sep = bi_export_get_key(key_val);
	split = ft_split_key_val(key_val, key_sep);
	if (split == NULL)
		handle_error(shell, ERROR_MSG_MEM, EXIT_FAILURE);
	if (!bi_export_is_valid_key(split[0]))
	{
		ft_free_str_array(&split);
		return (1);
	}
	if (ft_strcmp(key_sep, ENV_KEY_VALUE_SEPERATOR_APPEND_STR) == 0)
		returned = env_update_append(&(shell->env), split[0], split[1], false);
	else
		returned = env_update(&(shell->env), split[0], split[1], false);
	ft_free_str_array(&split);
	if (!returned && errno != 0)
		handle_error(shell, ERROR_MSG_MEM, EXIT_FAILURE);
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
