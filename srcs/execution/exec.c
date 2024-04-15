/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:15:29 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/15 12:32:32 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_node(t_minishell *shell, t_node *node, int fd[2], bool in_pipe)
{
	if (node == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	if (node->type == NODE_COMMAND)
		exec_node_command(shell, node, fd, in_pipe);
	else if (node->type == NODE_PIPE)
		exec_node_pipe(shell, node, fd);
	else if (node->type == NODE_AND || node->type == NODE_OR)
		exec_node_logical(shell, node, fd);
}
