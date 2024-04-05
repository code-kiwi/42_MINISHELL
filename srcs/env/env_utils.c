/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:17:49 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/04 14:13:09 by mhotting         ###   ########.fr       */
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
		split = ft_split_key_val(*envp, ENV_KEY_VALUE_SEPERATOR);
		if (split == NULL && errno != 0)
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

	if (env == NULL || key == NULL)
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
 *	Removes the t_env_element corresponding to the given key from env list.
 *	Updates the list pointer if necessary.
 */
void	env_delete(t_list **env, char *key)
{
	if (env == NULL || *env == NULL || key == NULL)
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
 *	Returns a NULL terminated array of all env_element key_value strings
 *	from the given env list.
 *	This could be used for env builtin and for generating an env adpted to
 *	execve().
 *	In case of ERROR, returns NULL.
 */
char	**env_get_all_array(t_list *env)
{
	size_t			size;
	size_t			i;
	char			**res;
	t_env_element	*env_elt;

	if (env == NULL)
		return (NULL);
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
