/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:17:49 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/03 02:18:35 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_list	*env_extract_process(char *str)
{
	char			**split;
	t_env_element	*env_elt;
	t_list			*new;

	if (str == NULL)
		return (NULL);
	split = ft_split(str, "=");
	if (split == NULL)
		return (NULL);
	if (split[0] == NULL || split[1] == NULL)
	{
		ft_free_str_array(&split);
		return (NULL);
	}
	env_elt = env_element_create(split[0], split[1]);
	ft_free_str_array(&split);
	if (env_elt == NULL)
		return (NULL);
	new = ft_lstnew((void *)env_elt);
	if (new == NULL)
		env_element_free(env_elt);
	return (new);
}

// ADD ERROR MESSAGE IF NO ENV?
t_list	*env_extract(char **envp)
{
	t_list	*env;
	t_list	*new;

	if (envp == NULL || *envp == NULL)
		return (NULL);
	env = NULL;
	while (*envp != NULL)
	{
		new = env_extract_process(*envp);
		if (new == NULL)
		{
			ft_lstclear(&env, env_element_free);
			return (NULL);
		}
		ft_lstadd_front(&env, new);
		++envp;
	}
	return (env);
}
