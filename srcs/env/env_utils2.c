/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:39:46 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/16 12:34:36 by mhotting         ###   ########.fr       */
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

/*
 *	Sets the given key read_only status to the given one into the given env
 *	Returns true on SUCCESS, false on ERROR
 *	Error cases:
 * 		- invalid arg
 * 		- unexisting key into env
*/
bool	env_set_readonly(t_list *env, char *key, bool read_only)
{
	t_list			*link;
	t_env_element	*env_elt;

	if (env == NULL || key == NULL || !env_exists(env, key))
		return (false);
	link = ft_lstfind(env, key, env_element_cmp);
	if (link == NULL)
		return (false);
	env_elt = (t_env_element *) link->content;
	if (env_elt == NULL)
		return (false);
	env_elt->read_only = read_only;
	return (true);
}

/*
 *	Returns a NULL terminated array of all env_element key_value strings
 *	from the given env list.
 *	This could be used for env builtin and for generating an env adpted to
 *	execve().
 *	NB: if the given env is NULL, an empty NULL terminated array is returned
 *	In case of ERROR, returns NULL.
 */
char	**env_get_all_array(t_list *env)
{
	size_t			size;
	size_t			i;
	char			**res;
	t_env_element	*env_elt;

	if (env == NULL)
		return (ft_split("", ""));
	size = ft_lstsize(env);
	res = (char **) ft_calloc(size + 1, sizeof(char *));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (env != NULL && i < size)
	{
		env_elt = (t_env_element *) env->content;
		res[i] = ft_strdup(env_elt->key_value);
		if (res[i] == NULL)
		{
			ft_free_str_array(&res);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	return (res);
}
