/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node_logical.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:41:09 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/15 12:57:00 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_node_logical_close_fds(int fds[2])
{
	if (fds[0] != FD_UNSET)
		fd_close_and_reset(&(fds[0]));
	if (fds[1] != FD_UNSET)
		fd_close_and_reset(&(fds[1]));
}

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
		exec_node_logical_close_fds(fds_src);
		exec_node_logical_close_fds(fds_dest);
		return (false);
	}
	return (true);
}

void	exec_node_logical(t_minishell *shell, t_node *node, int fd[2])
{
	int	child_right_fds[2];
	int	status;

	if (node == NULL || (node->type != NODE_AND && node->type != NODE_OR))
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	if (!exec_node_logical_clone_fds(fd, child_right_fds))
		handle_error(shell, ERROR_MSG_DUP, EXIT_FAILURE);
	exec_node(shell, node->child_left, fd, false);
	status = t_minishell_wait_pids(shell);
	// ADD status to env
	if (
		(node->type == NODE_AND && status != EXIT_SUCCESS)
		|| (node->type == NODE_OR && status == EXIT_SUCCESS)
	)
	{
		exec_node_logical_close_fds(child_right_fds);
		return ;
	}
	exec_node(shell, node->child_right, child_right_fds, false);
}
