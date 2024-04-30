/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node_logical.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:41:09 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/30 19:31:35 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "minishell.h"
#include "execution.h"
#include "node.h"
#include "signals.h"

/*
 *	Clones the files descriptors stored into fds_src into fds_dest
 *	Returns true on SUCCESS, false on ERROR
 *	Error cases:
 *		- call to dup() failed
 *	If an ERROR occurs, both all the fds are closed and reset to FD_UNSET
 */
static bool	exec_node_logical_clone_fds(int fds_src[2], int fds_dest[2])
{
	fds_dest[0] = FD_UNSET;
	fds_dest[1] = FD_UNSET;
	if (fds_src[0] != FD_UNSET)
		fds_dest[0] = dup(fds_src[0]);
	if (fds_src[1] != FD_UNSET)
		fds_dest[1] = dup(fds_src[1]);
	if (fds_dest[0] == -1 || fds_dest[1] == -1)
	{
		exec_node_close_fds(fds_src);
		exec_node_close_fds(fds_dest);
		return (false);
	}
	return (true);
}

/*
 *	Executes a node of type NODE_AND or NODE_OR into the given shell
 *	Executes the left child of the node, retrieves its execution status and,
 *	depending on it (and on the node type), executes the right child
 *	The given fds are duplicated in order to be able to use them into
 *	both child nodes (because the left child execution could close fds while
 *	the right child still needs them)
 *	In case of ERROR (internal errors such as memory problem, etc.) the shell
 *	stops its execution
 */
void	exec_node_logical(t_minishell *shell, t_node *node, int fds[2])
{
	int		child_right_fds[2];
	bool	interrupted;

	if (node == NULL || (node->type != NODE_AND && node->type != NODE_OR))
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	if (!exec_node_logical_clone_fds(fds, child_right_fds))
		handle_error(shell, ERROR_MSG_DUP, EXIT_FAILURE);
	exec_node(shell, node->child_left, fds, false);
	interrupted = !t_minishell_set_exec_status(shell);
	if (interrupted
		|| (node->type == NODE_AND && shell->status != EXIT_SUCCESS)
		|| (node->type == NODE_OR && shell->status == EXIT_SUCCESS)
	)
	{
		exec_node_close_fds(child_right_fds);
		return ;
	}
	exec_node(shell, node->child_right, child_right_fds, false);
}
