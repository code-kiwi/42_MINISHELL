/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:17:49 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/03 14:43:27 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Creates a chained list of t_env_element by extracting data from envp.
 *	envp has to have the format: "<KEY1>=<VALUE1>\n...<KEYN>=<VALUEN>"
 *	envp has to be NULL terminated.
 *	In case of ERROR, returns NULL, on SUCCESS, returns a pointer to the
 *	created list
 */
t_list	*env_extract(char **envp)
{
	t_list	*env;
	char	**split;
	bool	returned;

	if (envp == NULL || *envp == NULL)
		return (NULL);
	env = NULL;
	while (*envp != NULL)
	{
		split = ft_split(*envp, "=");
		if (split == NULL)
			return (ft_lstclear(&env, env_element_free), NULL);
		if (split[0] == NULL || split[1] == NULL)
		{
			ft_free_str_array(&split);
			++envp;
			continue ;
		}
		returned = env_add(&env, split[0], split[1]);
		ft_free_str_array(&split);
		if (!returned)
			return (ft_lstclear(&env, env_element_free), NULL);
		++envp;
	}
	return (env);
}

/*
 *	Returns the value corresponding to the given name inside of the env list.
 *	The returned value is returned as a freshly allocated string.
 *	If name is not stored into env, returns NULL.
 *	In case of ERROR, NULL is returned and errno is properly set.
 */
char	*env_get(t_list *env, char *name)
{
	t_list			*node;
	t_env_element	*env_elt;
	char			*value;

	if (env == NULL || name == NULL)
	{
		errno = ENODATA;
		return (NULL);
	}
	node = ft_lstfind(env, name, env_element_cmp);
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
 *	Removes the t_env_element corresponding to the given name from env list.
 *	Updates the list pointer if necessary.
 */
void	env_delete(t_list **env, char *name)
{
	if (env == NULL || *env == NULL || name == NULL)
		return ;
	ft_lst_remove_if(env, name, env_element_cmp, env_element_free);
}

/*
 *	Adds a new t_env_element into the env given list
 *	Updates the list pointer if necessary
 *	If the name was already defined into the list, the previous value is
 *	updated with the new one.
 *	Returns true on SUCCESS, false on ERROR
 *	Error cases:
 *		- wrong input (env and name cannot be NULL)
 *		- memory allocation failed
 */
bool	env_add(t_list **env, char *name, char *value)
{
	t_env_element	*env_elt;
	t_list			*new;

	if (env == NULL || name == NULL)
	{
		errno = ENODATA;
		return (false);
	}
	env_elt = env_element_create(name, value);
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
	env_delete(env, name);
	ft_lstadd_front(env, new);
	return (true);
}