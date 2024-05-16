/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_element_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 02:00:19 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/16 14:54:52 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "libft.h"
#include "minishell.h"
#include "env.h"

/*
 *	Allocates a t_env_element and returns a pointer to it.
 *	The key and value members are set with duplicate strings from given args.
 *	In case of ERROR, returns NULL
 *	Note: key cannot be NULL, value can be NULL, then the value member will
 *	be set to an empty string.
 */
t_env_element	*env_element_create(char *key, char *value, bool read_only)
{
	t_env_element	*env_elt;

	if (key == NULL)
		return (NULL);
	env_elt = (t_env_element *) ft_calloc(1, sizeof(t_env_element));
	if (env_elt == NULL)
		return (NULL);
	env_elt->key = ft_strdup(key);
	env_elt->value = ft_strdup(value);
	env_elt->key_value = NULL;
	if (value != NULL)
		env_elt->key_value = bridge(key, value, ENV_KEY_VALUE_SEPERATOR_STR);
	if (
		env_elt->key == NULL || (env_elt->value == NULL && errno != 0)
		|| (env_elt->key_value == NULL && errno != 0)
	)
	{
		env_element_free(env_elt);
		return (NULL);
	}
	env_elt->read_only = read_only;
	return (env_elt);
}

/*
 *	Frees the memory allocated to a t_env_element
 *	NOTE: This function takes a void * pointer in order to enable the use of
 *	ft_lstclear().
 */
void	env_element_free(void *env_elt_ptr)
{
	t_env_element	*env_elt;

	if (env_elt_ptr == NULL)
		return ;
	env_elt = (t_env_element *) env_elt_ptr;
	if (env_elt->key != NULL)
		free(env_elt->key);
	if (env_elt->value != NULL)
		free(env_elt->value);
	if (env_elt->key_value != NULL)
		free(env_elt->key_value);
	free(env_elt);
}

/*
 *	Compares a t_env_element key member to the given key argument.
 *	This function uses string comparison, and returns 0 if the keys are
 *	the same, a non-zero integer if they are different.
 *	NOTE: This function takes a void * pointer in order to enable the use of
 *	ft_lst_remove_if().
 */
int	env_element_cmp(void *env_elt_ptr, char *key)
{
	t_env_element	*env_elt;

	if (env_elt_ptr == NULL || key == NULL)
		return (-1);
	env_elt = (t_env_element *) env_elt_ptr;
	return (ft_strcmp(env_elt->key, key));
}

/*
 *	Updates the given env_elt with the given value
 *	Both value and key_value members of env_elt are updated
 *	Returns true on SUCCESS, false on ERROR
 *	NB: the old value are freed, the new values are freshly allocated strings
 *	NB: if value is NULL, it is considered like an empty string
 */
bool	env_element_update(
	t_env_element *env_elt, char *key, char *value, bool read_only
)
{
	char	*new_value;
	char	*new_key_value;

	if (env_elt == NULL || key == NULL || ft_strcmp(env_elt->key, key) != 0)
		return (false);
	if (env_elt->read_only || value == NULL)
		return (true);
	new_value = ft_strdup(value);
	new_key_value = NULL;
	if (value != NULL)
		new_key_value = bridge(key, value, ENV_KEY_VALUE_SEPERATOR_STR);
	if ((new_value == NULL && errno != 0)
		|| (new_key_value == NULL && errno != 0))
	{
		free(new_value);
		free(new_key_value);
		return (false);
	}
	free(env_elt->value);
	free(env_elt->key_value);
	env_elt->value = new_value;
	env_elt->key_value = new_key_value;
	env_elt->read_only = read_only;
	return (true);
}

/*
 *	Appends content to the given env_elt
 *	Updates its value by appending the given string to it
 *	Updates its key_value member
 *	Returns true on SUCCESS, false on ERROR
*/
bool	env_element_append(t_env_element *env_elt, char *key, char *to_append)
{
	char	*new_value;
	char	*curr_value;
	bool	ret;

	if (env_elt == NULL || key == NULL || ft_strcmp(env_elt->key, key) != 0)
		return (false);
	if (env_elt->read_only || to_append == NULL || *to_append == '\0')
		return (true);
	curr_value = env_elt->value;
	if (curr_value == NULL)
		new_value = ft_strjoin("", to_append);
	else
		new_value = ft_strjoin(curr_value, to_append);
	if (new_value == NULL)
		return (false);
	ret = env_element_update(env_elt, key, new_value, env_elt->read_only);
	free(new_value);
	return (ret);
}
