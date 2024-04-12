/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_node_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:39:49 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/12 15:46:19 by mhotting         ###   ########.fr       */
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
	t_redirection_list	*red;

	if (cmd == NULL)
		return ;
	red = cmd->redirection_list;
	exec_redirection_list(red);
	if (red->info.fd_stdin != FD_UNSET)
	{
		if (cmd->fd_in != FD_UNSET)
			fd_close_and_reset(&(cmd->fd_in));
		cmd->fd_in = red->info.fd_stdin;
		red->info.fd_stdin = FD_UNSET;
	}
	if (red->info.fd_stdout != FD_UNSET)
	{
		if (cmd->fd_out != FD_UNSET)
			fd_close_and_reset(&(cmd->fd_out));
		cmd->fd_out = red->info.fd_stdout;
		red->info.fd_stdout = FD_UNSET;
	}
}

static void	exec_cmd_process(t_minishell *shell, t_node_command *cmd, bool in_pipe)
{
	pid_t	pid;
	int		returned_status;

	if (shell == NULL || cmd == NULL || !cmd->argv || cmd->argv[0] == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	if (is_built_in(cmd->argv[0]) && !in_pipe)
	{
		returned_status = exec_builtin(shell, cmd);
		env_add_int(&(shell->env), "?", returned_status);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			handle_error(shell, ERROR_MSG_FORK, EXIT_FAILURE);
		if (pid == 0)
		{
			shell->is_child_process = true;
			exec_cmd(shell, cmd);
		}
		if (!t_minishell_add_pid(shell, pid))
			handle_error(shell, ERROR_MSG_MEM, EXIT_FAILURE);
	}
	node_command_close_fds(cmd);
}

void	exec_cmd_handler(
	t_minishell *shell, t_node *node, int fd_in, int fd_out, bool in_pipe
)
{
	t_node_command	*cmd;

	if (node == NULL || node->type != NODE_COMMAND || node->content == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	cmd = (t_node_command *) node->content;
	exec_cmd_set_pipe_fds(cmd, fd_in, fd_out);
	exec_cmd_set_redirections_fds(cmd);
	if (cmd->fd_in == FD_ERROR || cmd->fd_out == FD_ERROR)
	{
		node_command_close_fds(cmd);
		if (!t_minishell_add_pid(shell, PID_ERROR))
			handle_error(shell, ERROR_MSG_MEM, EXIT_FAILURE);
		return ;
	}
	exec_cmd_process(shell, cmd, in_pipe);
}
