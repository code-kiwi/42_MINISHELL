/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:17:49 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/16 14:52:26 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

#include "libft.h"
#include "minishell.h"
#include "env.h"

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
		split = ft_split_key_val(*envp, ENV_KEY_VALUE_SEPERATOR_STR);
		if (split == NULL)
			return (ft_lstclear(&env, env_element_free), NULL);
		if (split[0] == NULL || split[1] == NULL)
		{
			ft_free_str_array(&split);
			++envp;
			continue ;
		}
		returned = env_update(&env, split[0], split[1], false);
		ft_free_str_array(&split);
		if (!returned)
			return (ft_lstclear(&env, env_element_free), NULL);
		++envp;
	}
	return (env);
}

/*
 *	Removes the t_env_element corresponding to the given key from env list.
 *	Updates the list pointer if necessary.
 */
void	env_delete(t_list **env, char *key)
{
	t_list			*link;
	t_env_element	*env_elt;

	if (env == NULL || *env == NULL || key == NULL)
		return ;
	link = ft_lstfind(*env, key, env_element_cmp);
	if (link == NULL)
		return ;
	env_elt = (t_env_element *) link->content;
	if (env_elt == NULL)
		return ;
	if (env_elt->read_only)
		return ;
	ft_lst_remove_if(env, key, env_element_cmp, env_element_free);
}

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
static bool	env_add(t_list **env, char *key, char *value, bool read_only)
{
	t_env_element	*env_elt;
	t_list			*new;

	if (env == NULL || key == NULL)
	{
		errno = ENODATA;
		return (false);
	}
	env_elt = env_element_create(key, value, read_only);
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
	ft_lstadd_back(env, new);
	return (true);
}

/*
 *	Updates the given environment list at the given key position
 *	If the key is not stored into the list, then a new element is created
 *	If the key already exists but corresponds to a readonly var, nothing happens
 *	and true is returned
 *	Returns true on SUCCESS, false on ERROR
 */
bool	env_update(t_list **env, char *key, char *value, bool read_only)
{
	t_list			*link;
	t_env_element	*env_elt;

	if (env == NULL || key == NULL)
	{
		errno = ENODATA;
		return (false);
	}
	if (!env_exists(*env, key))
		return (env_add(env, key, value, read_only));
	link = ft_lstfind(*env, key, env_element_cmp);
	if (link == NULL)
		return (false);
	env_elt = (t_env_element *) link->content;
	if (env_elt == NULL)
		return (false);
	if (env_elt->read_only)
		return (true);
	return (env_element_update(env_elt, key, value, read_only));
}

/*
 *	Appends content into the given environment list at the given key position
 *	If the key is not stored into the list, then a new element is created
 *	If the key already exists but corresponds to a readonly var, nothing happens
 *	and true is returned
 *	Returns true on SUCCESS, false on ERROR
 */
bool	env_update_append(t_list **env, char *key, char *value, bool read_only)
{
	t_list			*link;
	t_env_element	*env_elt;

	if (env == NULL || key == NULL)
		return (false);
	if (!env_exists(*env, key))
		return (env_add(env, key, value, read_only));
	link = ft_lstfind(*env, key, env_element_cmp);
	if (link == NULL)
		return (false);
	env_elt = (t_env_element *) link->content;
	if (env_elt == NULL)
		return (false);
	if (env_elt->read_only)
		return (true);
	return (env_element_append(env_elt, key, value));
}
