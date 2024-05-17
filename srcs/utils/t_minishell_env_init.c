/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell_env_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:46:33 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/16 15:17:36 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>

#include "libft.h"
#include "minishell.h"
#include "env.h"

/*
 *	Initializes the SHLVL env variable into the given env
 *	No matter if it already existed, the value is set to the returned string of
 *	the getcwd function in order to avoid dummy PWD value inside of the env
 *	Returns true on SUCCESS, false on ERROR
 */
static bool	t_minishell_env_init_vars_pwd(t_list **env)
{
	char	*curr_path;
	bool	returned;

	curr_path = getcwd(NULL, 0);
	if (curr_path == NULL)
		return (false);
	returned = env_update(env, ENV_PWD, curr_path, false);
	free(curr_path);
	return (returned);
}

/*
 *	Initializes the "_" env variable into the given env
 *	No matter if it already existed, the value is set to the default value
 *	into the corresponding macro
 *	Returns true on SUCCESS, false on ERROR
 */
static bool	t_minishell_env_init_vars_underscore(t_list **env)
{
	return (env_update(env, ENV_UNDERSCORE, ENV_DEFAULT_UNDERSCORE, false));
}

/*
 *	Initializes the SHLVL env variable into the given env
 *	If SHLVL was already defined, updates it by adding one
 *	If it was not defined, its default value is 1
 *	Returns true on SUCCESS, false on ERROR
 *	NB: if the old SHLVL had reached INT_MAX, the SHLVL creation will fail
 */
static bool	t_minishell_env_init_vars_shlvl(t_list **env)
{
	char	*curr_val;
	int		nb;
	bool	returned;

	if (!env_exists(*env, ENV_SHLVL))
		returned = env_update(env, ENV_SHLVL, "1", false);
	else
	{
		curr_val = env_get(*env, ENV_SHLVL);
		if (curr_val == NULL)
			return (false);
		nb = ft_atoi(curr_val);
		free(curr_val);
		if (nb == INT_MAX)
			return (false);
		curr_val = ft_itoa(nb + 1);
		if (curr_val == NULL)
			return (false);
		returned = env_update(env, ENV_SHLVL, curr_val, false);
		free(curr_val);
	}
	return (returned);
}

/*
 *	Initializes some variables into the given environment
 *	Returns true on SUCCESS, false on ERROR
 */
static bool	t_minishell_env_init_vars(t_list **env)
{
	return (
		t_minishell_env_init_vars_shlvl(env)
		&& t_minishell_env_init_vars_pwd(env)
		&& t_minishell_env_init_vars_underscore(env)
	);
}

/*
 *	Returns a pointer to a t_list containig the shell's envrionment
 *	Initializes this env. using the given envp NULL terminated string array
 *	The performs some inner env. variable initializations
 *	In case of ERROR, returns NULL
 */
t_list	*t_minishell_env_init(char **envp)
{
	t_list	*env;

	if (envp == NULL)
		return (NULL);
	env = env_extract(envp);
	if (env == NULL && errno != 0)
		return (NULL);
	if (!t_minishell_env_init_vars(&env))
	{
		ft_lstclear(&env, env_element_free);
		return (NULL);
	}
	env_set_readonly(env, ENV_UNDERSCORE, true);
	return (env);
}
