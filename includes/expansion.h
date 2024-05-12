/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:31:28 by brappo            #+#    #+#             */
/*   Updated: 2024/05/12 11:40:21 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <stdlib.h>

typedef struct s_list		t_list;
typedef struct s_minishell	t_minishell;

# define O_QUOTE		1
# define O_VAR			2
# define O_PATH			4
# define O_IGN_QUOTE	8

void	get_variable_key_coordinates(char *input, ssize_t *coordinates,
			size_t variable_start);
ssize_t	expand_variable(char **input, size_t variable_start,
			bool double_quoted, t_minishell *shell);
t_list	*expand_wildcard(char *str, t_list *wildcards);
bool	string_equal_wildcard(char *str_wildcard,
			char *str_b, t_list *wildcards);
t_list	*expand_string(char **str, t_minishell *shell, char options);
bool	search_wildcards(char *input, t_list **wildcards_pos);
t_list	*lst_sort(t_list **to_sort, int (*cmp)(void *, void *));
bool	array_cat(void **dest, void **src, size_t dest_size);
size_t	array_size(void **array);
bool	expand_argv(char ***argv, char options, t_minishell *shell);
bool	expand_redirection(char **redirection, char options,
			t_minishell *shell);
#endif
