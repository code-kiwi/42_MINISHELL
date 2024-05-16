/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_all_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:26:28 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/16 14:43:13 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "env.h"

/**
 *	Returns a string representing the given env_elt
 *	If its value is not NULL, this string is an allocated copy of its key_val
 *	member
 *	If its value is NULL:
 *		- if get_null_value is true, the returned string is an
 *		allocated copy of env_elt->key
 *		- if get_null_value is false, the returned string is NULL
*/
static char	*get_current_env_elt_str(
	t_env_element *env_elt, bool get_null_value
)
{
	char	*res;

	if (env_elt == NULL)
		return (NULL);
	if (get_null_value && (!env_elt->value || !env_elt->key_value))
		res = ft_strdup(env_elt->key);
	else if (env_elt->key_value != NULL)
		res = ft_strdup(env_elt->key_value);
	else
		res = NULL;
	return (res);
}

/*
 *	Returns a NULL terminated array of all env_element key_value strings
 *	from the given env list.
 *	This can be used for env builtin and for generating an env adpted to
 *	execve().
 *	The get_null_value is used to handle env. variables with NULL value:
 *		- if true, they are added to the result array using their key
 *		- if false, they are ignored
 *	This option is useful for generating an array of strings adapted to the
 *	builtin 'export' when it is called with no argument
 *	NB: if the given env is NULL, an empty NULL terminated array is returned
 *	In case of ERROR, returns NULL.
 */
char	**env_get_all_array(t_list *env, bool get_null_value)
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
		env = env->next;
		if (!get_null_value && env_elt->value == NULL)
			continue ;
		res[i] = get_current_env_elt_str(env_elt, get_null_value);
		if (res[i] == NULL)
			return (ft_free_str_array(&res), NULL);
		i++;
	}
	return (res);
}
