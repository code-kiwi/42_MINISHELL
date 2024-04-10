/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_operator_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:01:32 by brappo            #+#    #+#             */
/*   Updated: 2024/04/10 12:01:48 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	add_pipe(t_node **current_node, t_node **head, t_list *tokens)
{
	t_node	*new_node;

	if (*head == NULL)
		return (false);
	new_node = node_pipe_create();
	if (new_node == NULL)
		return (false);
	new_node->child_left = *current_node;
	*current_node = new_node;
	return (get_nodes(&new_node->child_right, head, tokens->next));
}

bool	add_connector(t_node **current_node, t_node **head,
	t_list *tokens, t_token_type connector)
{
	t_node	*new_node;

	if (*head == NULL)
		return (false);
	if (connector == OPERATOR_AND_IF)
		new_node = node_and_create();
	else if (connector == OPERATOR_OR_IF)
		new_node = node_or_create();
	else
		return (false);
	if (new_node == NULL)
		return (false);
	new_node->child_left = *head;
	*head = new_node;
	return(get_nodes(&new_node->child_right, head, tokens->next));
}
