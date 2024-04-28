/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:39:46 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/26 12:00:31 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include "libft.h"
#include "env.h"

/*
 *	Returns the value corresponding to the given key inside of the env list.
 *	The returned value is returned as a freshly allocated string.
 *	If key is not stored into env, returns NULL.
 *	In case of ERROR, NULL is returned and errno is properly set.
 */
char	*env_get(t_list *env, char *key)
{
	t_list			*node;
	t_env_element	*env_elt;
	char			*value;

	if (key == NULL)
	{
		errno = ENODATA;
		return (NULL);
	}
	node = ft_lstfind(env, key, env_element_cmp);
	if (node == NULL || node->content == NULL)
		return (NULL);
	env_elt = (t_env_element *)(node->content);
	if (env_elt->value == NULL)
	{
		errno = ENODATA;
		return (NULL);
	}
	value = ft_strdup(env_elt->value);
	if (value == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	return (value);
}

/*
 *	Returns true if the key exists in the given env list, else returns false
 */
bool	env_exists(t_list *env, char *key)
{
	if (env == NULL || key == NULL)
		return (false);
	return (ft_lstfind(env, key, env_element_cmp) != NULL);
}
