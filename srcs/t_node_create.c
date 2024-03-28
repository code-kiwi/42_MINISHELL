/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_node_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:57:30 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/28 11:35:02 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Allocates a t_node and returns a pointer to it.
 *	The type member is set to the given type, the other members are set to NULL.
 *	In case of ERROR, returns NULL
 */
static t_node	*create_empty_node(t_node_type type)
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
 *	Allocates a t_node with an allocated t_node_pipe as content.
 *	Returns a pointer to the t_node.
 *	The t_node children are set to NULL.
 *	The t_node_pipe fd array components are set to FD_UNSET
 *	In case or ERROR, returns NULL
 */
t_node	*create_pipe_node(void)
{
	t_node		*node;
	t_node_pipe	*node_pipe;

	node = create_empty_node(NODE_PIPE);
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
 *	Allocates a t_node with an allocated t_node_command as content.
 *	Returns a pointer to the t_node.
 *	The t_node children are set to NULL.
 *	The t_node_command components are set using the arguments passed
 *	In case or ERROR, returns NULL
 */
t_node	*create_command_node(int argc, char **argv, t_redirection *redir)
{
	t_node			*node;
	t_node_command	*node_command;

	node = create_empty_node(NODE_COMMAND);
	if (node == NULL)
		return (NULL);
	node_command = (t_node_command *) malloc(sizeof(t_node_command));
	if (node_command == NULL)
	{
		free(node);
		return (NULL);
	}
	node_command->argc = argc;
	node_command->argv = argv;
	node_command->redirections = redir;
	node->content = (void *) node_command;
	return (node);
}
