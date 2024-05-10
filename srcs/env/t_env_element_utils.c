/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_element_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 02:00:19 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/10 16:57:07 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

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
t_env_element	*env_element_create(char *key, char *value)
{
	t_env_element	*env_elt;

	if (key == NULL)
		return (NULL);
	env_elt = (t_env_element *) ft_calloc(1, sizeof(t_env_element));
	if (env_elt == NULL)
		return (NULL);
	env_elt->key = ft_strdup(key);
	if (value == NULL)
		value = "";
	env_elt->value = ft_strdup(value);
	env_elt->key_value = bridge(key, value, ENV_KEY_VALUE_SEPERATOR_STR);
	if (
		env_elt->key == NULL || env_elt->value == NULL
		|| env_elt->key_value == NULL
	)
	{
		env_element_free(env_elt);
		return (NULL);
	}
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
 *	Displays the content of a t_env_element
 *	NOTE: This function takes a void * pointer in order to enable the use of
 *	ft_lstprint().
 */
void	env_element_print(void *env_elt_ptr)
{
	t_env_element	*env_elt;

	if (env_elt_ptr == NULL)
		return ;
	env_elt = (t_env_element *) env_elt_ptr;
	printf("----------\n");
	printf("env_element:\n");
	printf("\t- key: \"%s\"\n", env_elt->key);
	printf("\t- value: \"%s\"\n", env_elt->value);
	printf("\t- key_value: \"%s\"\n", env_elt->key_value);
	printf("\n");
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
bool	env_element_update(t_env_element *env_elt, char *key, char *value)
{
	char	*new_value;
	char	*new_key_value;

	if (env_elt == NULL || key == NULL || ft_strcmp(env_elt->key, key) != 0)
		return (false);
	if (value == NULL)
		value = "";
	new_value = ft_strdup(value);
	new_key_value = bridge(key, value, ENV_KEY_VALUE_SEPERATOR_STR);
	if (new_value == NULL || new_key_value == NULL)
	{
		free(new_value);
		free(new_key_value);
		return (false);
	}
	free(env_elt->value);
	free(env_elt->key_value);
	env_elt->value = new_value;
	env_elt->key_value = new_key_value;
	return (true);
}
