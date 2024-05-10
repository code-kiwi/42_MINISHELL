/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:43:07 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/10 16:56:11 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "libft.h"
#include "built_in.h"

/*
 *	Indicates if the given command name corresponds to a built-in function
 *	into the given bi_funcs array
 *	Returns true if the name is a built-in, else returns false
 */
bool	is_built_in(t_bi_component bi_funcs[NB_BUILT_IN], char *cmd_name)
{
	if (cmd_name == NULL)
		return (false);
	return (built_in_get(bi_funcs, cmd_name) != NULL);
}

/*
 *	Returns a pointer to the built-in function corresponding to the given
 *	cmd_name into bi_funcs array
 *	If the function has not been found, returns NULL
 */
t_bi_func	built_in_get(t_bi_component bi_funcs[NB_BUILT_IN], char *cmd_name)
{
	size_t	i;

	if (cmd_name == NULL)
		return (NULL);
	i = 0;
	while (i < NB_BUILT_IN)
	{
		if (ft_strcmp(cmd_name, bi_funcs[i].name) == 0)
			return (bi_funcs[i].func);
		i++;
	}
	return (NULL);
}

/*
 *	Sets the bi_funcs array whose elements are t_bi_component elements: a key
 *	pointer pair where key is the function name and the pointer is a pointer to
 *	the corresponding built-in function
 */
void	built_in_init_array(t_bi_component bi_funcs[NB_BUILT_IN])
{
	bi_funcs[0].name = "echo";
	bi_funcs[0].func = bi_echo;
	bi_funcs[1].name = "cd";
	bi_funcs[1].func = bi_cd;
	bi_funcs[2].name = "pwd";
	bi_funcs[2].func = bi_pwd;
	bi_funcs[3].name = "export";
	bi_funcs[3].func = bi_export;
	bi_funcs[4].name = "unset";
	bi_funcs[4].func = bi_unset;
	bi_funcs[5].name = "env";
	bi_funcs[5].func = bi_env;
	bi_funcs[6].name = "exit";
	bi_funcs[6].func = bi_exit;
}
