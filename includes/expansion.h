/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:31:28 by brappo            #+#    #+#             */
/*   Updated: 2024/04/17 12:34:11 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include "minishell.h"

typedef struct s_minishell	t_minishell;

void	get_variable_key_coordinates(char *input, ssize_t *coordinates,
			size_t variable_start);
ssize_t	expand_variable(char **input, size_t variable_start,
			bool double_quoted, t_minishell *shell);
t_list	*expand_wildcard(char *str, t_list *wildcards);
bool	string_equal_wildcard(char *str_wildcard,
			char *str_b, t_list *wildcards);
t_list	*expand_string(t_token *token, t_minishell *shell);
bool	search_wildcards(char *input, t_list **wildcards_pos);

#endif // !EXPANSION_H