/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:11:12 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/29 10:01:05 by mhotting         ###   ########.fr       */
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
 *	A valid key start with a letter or an '_' and is composed of alphanumeric or
 *	'_' chars
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

/*
 *	Parses the given key_val string in order to return the appropriate key
 *	among "=", "+="
 *	If both keys are met, the first one found is returned
 *	If no key is found, NULL is returned
 *	If only one key is found, then it is returned
*/
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
		ft_dprintf(STDERR_FILENO, EXPORT_MSG_ERR_KEY, split[0]);
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
 *	Writes the declared env vars from shell->env into the given fd_out
 *	Returns EXIT_SUCCESS on SUCCESS, EXIT_FAILURE on ERROR
 * 
*/
static int	bi_export_no_arg(t_minishell *shell, int fd_out)
{
	char	**env_str;
	size_t	i;

	env_str = env_get_all_array(shell->env, true);
	if (env_str == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (env_str[i] != NULL)
	{
		if (ft_dprintf(fd_out, EXPORT_NO_ARG_STR, env_str[i]) == -1)
		{
			ft_free_str_array(&env_str);
			return (EXIT_FAILURE);
		}
		i++;
	}
	ft_free_str_array(&env_str);
	return (EXIT_SUCCESS);
}

/*
 *	Sets variables into the given shell's environment
 *	The expected strings into argv are: "KEY=VALUE"
 *	Multiple keys can be assigned in one call
 *	Returns EXIT_SUCCESS on SUCCESS, EXIT_FAILURE on ERROR
 *	NB: if no argument is provided, the functions writes the declared env vars.
 *	into the given fd_out
 */
int	bi_export(t_minishell *shell, char **argv, int fd_out)
{
	size_t	i;
	int		returned;

	if (shell == NULL || argv == NULL || argv[0] == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	returned = 0;
	if (argv[1] == NULL)
		return (bi_export_no_arg(shell, fd_out));
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
