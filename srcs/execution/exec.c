/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:15:29 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/16 12:43:59 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Closes the file descriptors stored into the given fds array
 *	The values are reset to FD_UNSET
 */
void	exec_node_close_fds(int fds[2])
{
	if (fds[0] != -1 && fds[0] != FD_UNSET)
		fd_close_and_reset(&(fds[0]));
	if (fds[1] != -1 && fds[1] != FD_UNSET)
		fd_close_and_reset(&(fds[1]));
}

/*
 *	Executes the AST stored into the shell
 *	Frees the memory used for this AST
 *	Waits for all the commands to be executed to update shell's execution status
 */
void	exec_ast(t_minishell *shell)
{
	int	fd[2];

	if (shell == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	fd[0] = FD_UNSET;
	fd[1] = FD_UNSET;
	exec_node(shell, shell->ast, fd, false);
	ast_free(&(shell->ast));
	t_minishell_get_exec_status(shell);
}

/*
 *	Executes the given node into the given shell
 *	This functions acts like a dispatcher which will call the right node
 *	execution function depending on the node type
 *	The node stdin and stdout are stored into fd (for pipe redirections)
 *	The in_pipe boolean indicates if we are in the context of a pipe
 */
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
