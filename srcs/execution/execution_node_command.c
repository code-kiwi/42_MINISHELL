/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_node_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:39:49 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/10 16:23:35 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd_set_pipe_fds(t_node_command *cmd, int fd_in, int fd_out)
{
	if (cmd == NULL)
		return ;
	cmd->fd_in = fd_in;
	cmd->fd_out = fd_out;
}

static void	exec_cmd_set_redirections_fds(t_node_command *cmd)
{
	if (cmd == NULL)
		return ;
}

static void	exec_cmd(t_minishell *shell, t_node *node)
{
	if (shell == NULL || node == NULL)
		exit(EXIT_FAILURE);
	node_free_single(&node);
	t_minishell_free(shell);
	exit(EXIT_SUCCESS);
}

// CHECK ERROR CASE (ADD PID_ERROR TO LIST?)
void	exec_cmd_handler(t_minishell *shell, t_node *node, int fd_in, int fd_out)
{
	t_node_command	*cmd;
	pid_t			pid;

	if (node == NULL || node->type != NODE_COMMAND || node->content == NULL)
		return ;
	cmd = (t_node_command *) node->content;
	exec_cmd_set_pipe_fds(cmd, fd_in, fd_out);
	redirection_list_exec(cmd->redirection_list);
	exec_cmd_set_redirections_fds(cmd);
	if (cmd->fd_in == FD_ERROR || cmd->fd_out == FD_ERROR)
	{
		node_command_close_fds(node);
		if (!t_minishell_add_pid(shell, PID_ERROR))
			handle_error(shell, ERROR_MSG_MEM, EXIT_FAILURE);
		return ;
	}
	pid = fork();
	if (pid == -1)
		handle_error(shell, ERROR_MSG_FORK, EXIT_FAILURE);
	if (pid == 0)
		exec_cmd(shell, node);
	if (!t_minishell_add_pid(shell, pid))
		handle_error(shell, ERROR_MSG_MEM, EXIT_FAILURE);
	node_command_close_fds(node);
}
