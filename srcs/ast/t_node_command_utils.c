/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_node_command_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:54:42 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/11 11:27:11 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Allocates a t_node with an allocated t_node_command as content.
 *	Returns a pointer to the t_node.
 *	The t_node children are set to NULL.
 *	The t_node_command components are set using the arguments passed
 *	In case or ERROR, returns NULL
 */
t_node	*node_command_create(int argc, char **argv)
{
	t_node			*node;
	t_node_command	*node_command;

	if (argv == NULL)
		return (NULL);
	node = node_create_empty(NODE_COMMAND);
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
	node_command->redirection_list = redirection_list_create();
	if (node_command->redirection_list == NULL)
	{
		free(node_command);
		free(node);
		return (NULL);
	}
	node->content = (void *) node_command;
	return (node);
}

/*
 *	Frees the memory allocated to a t_node_command
 *	Frees its argv component (frees all the strings contained in this argv)
 *	Frees the redirections component
 *	Frees the t_node_command itself and sets the pointer to NULL
 */
void	node_command_free(void **node_ptr)
{
	t_node_command	*node;

	if (node_ptr == NULL || *node_ptr == NULL)
		return ;
	node = (t_node_command *) *node_ptr;
	free(node->argv);
	redirection_list_free(&(node->redirection_list));
	free(node);
	*node_ptr = NULL;
}

/*
 *	Adds a new redirection to a t_node of type NODE_COMMAND
 *	This node element has to be a t_node_command element (node type important)
 *	Returns true on SUCCESS
 *	Returns false on ERROR
 *	Error cases:
 *		- bad parameters given to the function
 *		- impossible to add a redirection
 */
bool	node_command_add_redirection(t_node *node, char *op, char *filename)
{
	t_node_command		*cmd;

	if (
		node == NULL || op == NULL || filename == NULL
		|| node->type != NODE_COMMAND || node->content == NULL
	)
		return (false);
	cmd = (t_node_command *) node->content;
	return (redirection_list_add(cmd->redirection_list, op, filename));
}
