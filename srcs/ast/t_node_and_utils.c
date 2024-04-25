/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_node_and_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:05:19 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/25 11:02:02 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "node.h"

/*
 *	Allocates a t_node of NODE_AND type.
 *	Returns a pointer to the t_node.
 *	The t_node children are set to NULL.
 *	The content is set to NULL because a NODE_AND node does not need to handle
 *	any content.
 *	In case or ERROR, returns NULL
 */
t_node	*node_and_create(void)
{
	t_node		*node;

	node = node_create_empty(NODE_AND);
	if (node == NULL)
		return (NULL);
	node->content = NULL;
	return (node);
}

/*
 *	Frees the memory allocated to a t_node of type NODE_AND
 */
void	node_and_free(void **node_ptr)
{
	if (node_ptr == NULL || *node_ptr == NULL)
		return ;
	free(*node_ptr);
	*node_ptr = NULL;
}
