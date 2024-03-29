/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_node_pipe_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:58:05 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/29 10:18:42 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Allocates a t_node with an allocated t_node_pipe as content.
 *	Returns a pointer to the t_node.
 *	The t_node children are set to NULL.
 *	The t_node_pipe fd array components are set to FD_UNSET
 *	In case or ERROR, returns NULL
 */
t_node	*node_pipe_create(void)
{
	t_node		*node;
	t_node_pipe	*node_pipe;

	node = node_create_empty(NODE_PIPE);
	if (node == NULL)
		return (NULL);
	node_pipe = (t_node_pipe *) malloc(sizeof(t_node_pipe));
	if (node_pipe == NULL)
	{
		free(node);
		return (NULL);
	}
	(node_pipe->fd)[0] = FD_UNSET;
	(node_pipe->fd)[1] = FD_UNSET;
	node->content = (void *) node_pipe;
	return (node);
}

/*
 *	Frees the memory allocated to a t_node_pipe
 *	Frees its argv component (frees all the strings contained in this argv)
 *	Frees the redirection component
 *	Frees the t_node_command itself and sets the pointer to NULL
 */
void	node_pipe_free(void **node_ptr)
{
	t_node_pipe	*node;

	if (node_ptr == NULL || *node_ptr == NULL)
		return ;
	node = (t_node_pipe *) *node_ptr;
	if ((node->fd)[0] != FD_UNSET)
		close_file_descriptor((node->fd)[0]);
	if ((node->fd)[1] != FD_UNSET)
		close_file_descriptor((node->fd)[1]);
	free(node);
	*node_ptr = NULL;
}
