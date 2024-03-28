/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_node_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:21:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/28 11:37:45 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Frees the memory allocated to a t_node element
 *	Frees the node content depending on its type
 *	Frees the node pointer and sets it to NULL
 */
static void	free_single_node(t_node **node_ptr)
{
	t_node	*node;

	if (node_ptr == NULL || *node_ptr == NULL)
		return ;
	node = *node_ptr;
	if (node->type == NODE_COMMAND)
		free_node_content_command(&(node->content));
	else if (node->type == NODE_PIPE)
		free_node_content_pipe(&(node->content));
	free(node);
	*node_ptr = NULL;
}

/*
 *	Frees all the memory allocated to the given AST
 *	Takes the top node and frees the tree recursively
 *	Sets the top node pointer to NULL
 */
void	free_ast(t_node **node_ptr)
{
	t_node	*node;

	if (node_ptr == NULL || *node_ptr == NULL)
		return ;
	node = *node_ptr;
	free_ast(&(node->child_left));
	free_ast(&(node->child_right));
	free_single_node(node_ptr);
	*node_ptr = NULL;
}
