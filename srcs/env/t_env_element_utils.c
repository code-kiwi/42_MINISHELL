/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_element_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 02:00:19 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/03 10:26:45 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_element	*env_element_create(char *name, char *value)
{
	t_env_element	*env_elt;

	if (name == NULL || value == NULL)
		return (NULL);
	env_elt = (t_env_element *) ft_calloc(1, sizeof(t_env_element));
	if (env_elt == NULL)
		return (NULL);
	env_elt->name = ft_strdup(name);
	env_elt->value = ft_strdup(value);
	if (env_elt->name == NULL || env_elt->value == NULL)
	{
		env_element_free(env_elt);
		return (NULL);
	}
	return (env_elt);
}

void	env_element_free(void *env_elt_ptr)
{
	t_env_element	*env_elt;

	if (env_elt_ptr == NULL)
		return ;
	env_elt = (t_env_element *) env_elt_ptr;
	if (env_elt->name != NULL)
		free(env_elt->name);
	if (env_elt->value != NULL)
		free(env_elt->value);
	free(env_elt);
}

void	env_element_print(void *env_elt_ptr)
{
	t_env_element	*env_elt;

	if (env_elt_ptr == NULL)
		return ;
	env_elt = (t_env_element *) env_elt_ptr;
	printf("----------\n");
	printf("env_element:\n");
	printf("\t- name: \"%s\"\n", env_elt->name);
	printf("\t- value: \"%s\"\n", env_elt->value);
	printf("\n");
}

int	env_element_cmp(void *env_elt_ptr, char *name)
{
	t_env_element	*env_elt;

	if (env_elt_ptr == NULL || name == NULL)
		return (-1);
	env_elt = (t_env_element *) env_elt_ptr;
	return (ft_strcmp(env_elt->name, name));
}
