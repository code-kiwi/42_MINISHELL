/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_node_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:51:37 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/10 16:55:28 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "node.h"

/*
 *	Allocates a t_node and returns a pointer to it.
 *	The type member is set to the given type, the other members are set to NULL.
 *	In case of ERROR, returns NULL
 */
t_node	*node_create_empty(t_node_type type)
{
	t_node	*node;

	if (type < 0 || type >= NUM_NODE_TYPE)
		return (NULL);
	node = (t_node *) malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	ft_memset(node, 0, sizeof(t_node));
	node->type = type;
	return (node);
}

/*
 *	Frees the memory allocated to a t_node element
 *	Frees the node content depending on its type
 *	Frees the node pointer and sets it to NULL
 */
void	node_free_single(t_node **node_ptr)
{
	t_node	*node;

	if (node_ptr == NULL || *node_ptr == NULL)
		return ;
	node = *node_ptr;
	if (node->type == NODE_COMMAND)
		node_command_free(&(node->content));
	else if (node->type == NODE_PIPE)
		node_pipe_free(&(node->content));
	else if (node->type == NODE_AND)
		node_and_free(&(node->content));
	else if (node->type == NODE_OR)
		node_or_free(&(node->content));
	else if (node->type == NODE_SUBSHELL)
		node_subshell_free(&(node->content));
	free(node);
	*node_ptr = NULL;
}

/*
 *	Frees all the memory allocated to the given AST
 *	Takes the top node and frees the tree recursively
 *	Sets the top node pointer to NULL
 */
void	ast_free(t_node **node_ptr)
{
	t_node	*node;

	if (node_ptr == NULL || *node_ptr == NULL)
		return ;
	node = *node_ptr;
	ast_free(&(node->child_left));
	ast_free(&(node->child_right));
	node_free_single(node_ptr);
	*node_ptr = NULL;
}
