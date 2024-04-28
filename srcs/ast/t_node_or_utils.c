/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_node_or_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:05:58 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/25 11:07:34 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "node.h"

/*
 *	Allocates a t_node of NODE_OR type.
 *	Returns a pointer to the t_node.
 *	The t_node children are set to NULL.
 *	The content is set to NULL because a NODE_OR node does not need to handle
 *	any content.
 *	In case or ERROR, returns NULL
 */
t_node	*node_or_create(void)
{
	t_node		*node;

	node = node_create_empty(NODE_OR);
	if (node == NULL)
		return (NULL);
	node->content = NULL;
	return (node);
}

/*
 *	Frees the memory allocated to a t_node of type NODE_AND
 */
void	node_or_free(void **node_ptr)
{
	if (node_ptr == NULL || *node_ptr == NULL)
		return ;
	free(*node_ptr);
	*node_ptr = NULL;
}
