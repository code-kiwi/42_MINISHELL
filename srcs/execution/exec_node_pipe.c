/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:49:27 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/14 20:54:47 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_node_pipe(t_minishell *shell, t_node *node, int fd[2])
{
	t_node_pipe	*node_pipe;
	int			child_fds[2];

	if (node == NULL || node->type != NODE_PIPE || node->content == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	node_pipe = (t_node_pipe *) node->content;
	if (pipe(node_pipe->fd) == -1)
		handle_error(shell, ERROR_MSG_PIPE, EXIT_FAILURE);
	child_fds[0] = fd[0];
	child_fds[1] = node_pipe->fd[1];
	node_pipe->fd[1] = FD_UNSET;
	exec_node(shell, node->child_left, child_fds, true);
	child_fds[0] = node_pipe->fd[0];
	child_fds[1] = FD_UNSET;
	node_pipe->fd[0] = FD_UNSET;
	exec_node(shell, node->child_right, child_fds, true);
}
