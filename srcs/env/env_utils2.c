/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:17:49 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/13 17:01:39 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Adds a new t_env_element into the env given list
 *	Updates the list pointer if necessary
 *	If the key was already defined into the list, the previous value is
 *	updated with the new one.
 *	Returns true on SUCCESS, false on ERROR
 *	Error cases:
 *		- wrong input (env and key cannot be NULL)
 *		- memory allocation failed
 */
bool	env_add(t_list **env, char *key, char *value)
{
	t_env_element	*env_elt;
	t_list			*new;

	if (env == NULL || key == NULL)
	{
		errno = ENODATA;
		return (false);
	}
	env_elt = env_element_create(key, value);
	if (env_elt == NULL)
	{
		errno = ENOMEM;
		return (false);
	}
	new = ft_lstnew((void *)env_elt);
	if (new == NULL)
	{
		env_element_free(env_elt);
		errno = ENOMEM;
		return (false);
	}
	env_delete(env, key);
	ft_lstadd_front(env, new);
	return (true);
}

/*
 *	Adds a new element into the env given list
 *	Calls the env_add() function after having converted the interger
 *	given value to a string.
 *	Returns true on SUCCESS, false on ERROR
 *	Error cases:
 *		- wrong input (env and key cannot be NULL)
 *		- memory allocation failed for value conversion
 *		- call to env_add() failed
 */
bool	env_add_int(t_list **env, char *key, int value)
{
	char	*value_to_str;
	bool	returned;

	if (env == NULL || key == NULL)
		return (false);
	value_to_str = ft_itoa(value);
	if (value_to_str == NULL)
		return (false);
	returned = env_add(env, key, value_to_str);
	free(value_to_str);
	return (returned);
}
