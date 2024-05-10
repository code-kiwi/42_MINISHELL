/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:37:10 by brappo            #+#    #+#             */
/*   Updated: 2024/05/10 16:53:22 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILD_AST_H
# define BUILD_AST_H

# include <stdbool.h>
# include <stdlib.h>

typedef struct s_list		t_list;
typedef struct s_node		t_node;
typedef enum e_token_type	t_token_type;
typedef struct s_token		t_token;

bool	set_operator_type(t_list *tokens);
size_t	array_size(void **array);
bool	get_nodes(t_node **current_node, t_node **head, t_list *tokens);
bool	is_redirection(t_token_type token_type);
bool	add_pipe(t_node **current_node, t_node **head, t_list *tokens);
bool	add_command(t_node **current_node, t_node **head, t_list *tokens);
bool	add_subshell(t_node **current_node, t_node **head, t_list *tokens);
t_node	*build_ast(t_list *tokens);
char	**get_argv(t_list *tokens);
bool	is_cmd_token(t_list *tokens);
bool	add_connector(t_node **current_node, t_node **head,
			t_list *tokens, t_token_type connector);
void	ast_syntax_error(t_token *token);

#endif
