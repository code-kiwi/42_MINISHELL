/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:14:38 by brappo            #+#    #+#             */
/*   Updated: 2024/04/10 11:13:44 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	add_pipe(t_node **current_node, t_node **head, t_list *tokens)
{
	t_node	*new_node;

	if (*head == NULL)
		return (false);
	new_node = node_create_empty(NODE_PIPE);
	if (new_node == NULL)
		return (false);
	new_node->child_left = *current_node;
	*current_node = new_node;
	return (get_nodes(&new_node->child_right, head, tokens->next));
}

bool	add_connector(t_node **current_node, t_node **head, t_list *tokens)
{
	t_node	*new_node;

	if (*head == NULL)
		return (false);
	new_node = 
}

t_node *build_ast(t_list *tokens)
{
	t_node	*current_node;
	t_node	*head;

	current_node = NULL;
	head = NULL;
	if (set_operator_type(tokens) == false)
		return (NULL);
	get_nodes(&current_node, &head, tokens);
}

bool	get_nodes(t_node **current_node, t_node **head, t_list *tokens)
{
	t_token			*first_token;
	t_token_type	token_type;

	if (current_node == NULL || head == NULL || tokens == NULL)
		return (false);
	first_token = (t_token *)tokens->content;
	token_type = first_token->type;
	if (token_type == END)
		return (true);
	if (token_type == OPERATOR_PIPE)
		return (add_pipe(current_node, head, tokens));
	if (token_type == OPERATOR_OR_IF || token_type == OPERATOR_AND_IF)
		return (add_connector(current_node, head, tokens));
	if (is_subshell(tokens))
		return (add_subshell(current_node, head, tokens));
	return (add_command(current_node, head, tokens));
}