/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:11:12 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/26 14:41:40 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include "libft.h"
#include "minishell.h"
#include "env.h"

static bool	bi_export_var(t_minishell *shell, char *key_val)
{
	char	**split;
	bool	returned;

	split = ft_split_key_val(key_val, ENV_KEY_VALUE_SEPERATOR);
	if (split == NULL && errno != 0)
		return (false);
	if (split[0] == NULL || split[1] == NULL)
	{
		ft_free_str_array(&split);
		return (true);
	}
	returned = env_add(&(shell->env), split[0], split[1]);
	ft_free_str_array(&split);
	return (returned);
}

int	bi_export(t_minishell *shell, char **argv)
{
	size_t	i;
	bool	error_flag;

	if (shell == NULL || argv == NULL || argv[0] == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	i = 1;
	while (argv[i] != NULL)
	{
		error_flag = error_flag || bi_export_var(shell, argv[i]);
		i++;
	}
	if (error_flag)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
