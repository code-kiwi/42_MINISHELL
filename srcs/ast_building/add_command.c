/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:00:04 by brappo            #+#    #+#             */
/*   Updated: 2024/04/10 12:45:40 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	add_command(t_node **current_node, t_node **head, t_list *tokens)
{
	t_node	*new_node;

	new_node = node_create_empty(NODE_COMMAND);
	if (new_node == NULL)
		return (false);
	*current_node = new_node;
	if (*head == NULL)
		*head = new_node;
	return (get_nodes(current_node, head, tokens->next));
}
