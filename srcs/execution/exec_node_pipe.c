/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:49:27 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/17 11:57:09 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Executes a node of type NODE_PIPE into the given shell
 *	Steps:
 *		- opens a pipe
 *		- sets left chidls's fds
 *		- executes left child -> writes into the pipe
 *		- sets right chidls's fds
 *		- executes right child -> reads from the path
 *	The pipe does not manage to close its pipe fds, because left and right
 *	children will close them if it is necessary
 */
void	exec_node_pipe(t_minishell *shell, t_node *node, int fds[2])
{
	t_node_pipe	*node_pipe;
	int			child_fds[2];

	if (node == NULL || node->type != NODE_PIPE || node->content == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	node_pipe = (t_node_pipe *) node->content;
	if (pipe(node_pipe->fd) == -1)
	{
		exec_node_close_fds(fds);
		handle_error(shell, ERROR_MSG_PIPE, EXIT_FAILURE);
	}
	child_fds[0] = fds[0];
	child_fds[1] = node_pipe->fd[1];
	node_pipe->fd[1] = FD_UNSET;
	exec_node(shell, node->child_left, child_fds, true);
	child_fds[0] = node_pipe->fd[0];
	child_fds[1] = fds[1];
	node_pipe->fd[0] = FD_UNSET;
	exec_node(shell, node->child_right, child_fds, true);
}
