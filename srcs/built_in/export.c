/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:11:12 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/06 15:06:56 by mhotting         ###   ########.fr       */
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
 *	Given a key_val string, adds the key/value pair into the given shell's
 *	environment
 *	Returns true on SUCCESS, false on ERROR
 */
static bool	bi_export_var(t_minishell *shell, char *key_val)
{
	char	**split;
	bool	returned;

	split = ft_split_key_val(key_val, ENV_KEY_VALUE_SEPERATOR);
	if (split == NULL)
		return (false);
	if (split[0] == NULL || split[1] == NULL)
	{
		ft_free_str_array(&split);
		return (true);
	}
	if (!bi_export_is_valid_key(split[0]))
	{
		ft_dprintf(STDERR_FILENO, EXPORT_MSG_ERR_KEY, split[1]);
		ft_free_str_array(&split);
		return (false);
	}
	returned = env_update(&(shell->env), split[0], split[1]);
	ft_free_str_array(&split);
	return (returned);
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
	bool	error_flag;

	if (shell == NULL || argv == NULL || argv[0] == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	(void) fd_out;
	error_flag = false;
	i = 1;
	while (argv[i] != NULL)
	{
		error_flag = bi_export_var(shell, argv[i]) || error_flag;
		i++;
	}
	if (error_flag)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
