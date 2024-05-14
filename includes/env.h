/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 23:48:56 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/26 13:18:17 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# define ENV_KEY_VALUE_SEPERATOR		'='
# define ENV_KEY_VALUE_SEPERATOR_STR	"="

typedef struct s_list	t_list;

typedef struct s_env_element
{
	char	*key;
	char	*value;
	char	*key_value;

}	t_env_element;

// env general functions
t_list			*env_extract(char **envp);
void			env_delete(t_list **env, char *key);
bool			env_add(t_list **env, char *key, char *value);
bool			env_update(t_list **env, char *key, char *value);
char			**env_get_all_array(t_list *env);
char			*env_get(t_list *env, char *key);
bool			env_exists(t_list *env, char *key);

// t_env_element functions
t_env_element	*env_element_create(char *key, char *value);
bool			env_element_update(t_env_element *env_elt, char *k, char *v);
void			env_element_free(void *env_elt_ptr);
int				env_element_cmp(void *env_elt_ptr, char *key);

#endif
