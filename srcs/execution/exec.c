/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:15:29 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/10 16:57:12 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "minishell.h"
#include "execution.h"
#include "node.h"

/*
 *	Executes the given node into the given shell
 *	This functions acts like a dispatcher which will call the right node
 *	execution function depending on the node type
 *	The node stdin and stdout are stored into fd (for pipe redirections)
 *	The in_pipe boolean indicates if we are in the context of a pipe
 */
void	exec_node(t_minishell *shell, t_node *node, int fds[2], bool in_pipe)
{
	if (node == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	if (node->type == NODE_COMMAND)
		exec_node_command(shell, node, fds, in_pipe);
	else if (node->type == NODE_PIPE)
		exec_node_pipe(shell, node, fds);
	else if (node->type == NODE_AND || node->type == NODE_OR)
		exec_node_logical(shell, node, fds);
	else if (node->type == NODE_SUBSHELL)
		exec_node_subshell(shell, node, fds);
}

/*
 *	Executes the AST stored into the shell
 *	Frees the memory used for this AST
 *	Waits for all the commands to be executed to update shell's execution status
 */
void	exec_ast(t_minishell *shell, int fds_given[2])
{
	int	fds_to_pass[2];

	if (shell == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	if (fds_given != NULL)
	{
		fds_to_pass[0] = fds_given[0];
		fds_to_pass[1] = fds_given[1];
	}
	else
	{
		fds_to_pass[0] = FD_UNSET;
		fds_to_pass[1] = FD_UNSET;
	}
	exec_node(shell, shell->ast, fds_to_pass, false);
	t_minishell_set_exec_status(shell);
}
