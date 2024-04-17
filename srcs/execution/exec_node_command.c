/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:39:49 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/15 02:11:35 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Sets command file descriptors according to the given ones
 */
static void	exec_cmd_set_pipe_fds(t_node_command *cmd, int fd_in, int fd_out)
{
	if (cmd == NULL)
		return ;
	cmd->fd_in = fd_in;
	cmd->fd_out = fd_out;
}

/*
 *	Sets the final command's file descriptors according to the command's
 *	redirection_list member
 *	Steps:
 *		- executes the command redirections 
 *		- sets the cmd file descriptors according to the redirection
 *		execution results
 *	If the command already had valid opened file desciptors, they are
 *	overwritten by the new ones (after having been closed)
 *	If there is no redirection to operate, the command's fds remain unchanged
 */
static void	exec_cmd_set_redirections_fds(t_node_command *cmd)
{
	t_redirection_list	*red;

	if (cmd == NULL || cmd->redirection_list == NULL)
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

/*
 *	Executes the given command
 *	A subprocess is created for the execution, except if we are outside of a
 *	pipe and calling a builtin function
 *	If a builtin is called outside of a pipe, the builtin is executed and the
 *	shell env last status is set using the returned status from the builtin
 *	If we are in a subprocess:
 *		- We fork
 *		- The subprocess executes the command (or builtin)
 *		- The main process adds the subprocess' pid to the shell's pid list
 *	Then the command's file descriptors are closed
 */
static void	exec_cmd_process(
	t_minishell *shell, t_node_command *cmd, bool in_pipe
)
{
	pid_t	pid;

	if (shell == NULL || cmd == NULL || !cmd->argv || cmd->argv[0] == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	if (is_built_in(cmd->argv[0]) && !in_pipe)
		shell->status = exec_builtin(shell, cmd);
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

/*
 *	Executes the given node of type command
 *	Steps:
 *		- checks the input args (valid shell, valid command node)
 *		- sets the command file descriptors according to the given ones
 *		(given fd[0] will be command's stdin, fd[1] command's stdout)
 *		- sets the command redirections according to command's redirection
 *		list member
 *		- test if there was a redirection error
 *		- executes the command
 */
void	exec_node_command(
	t_minishell *shell, t_node *node, int fd[2], bool in_pipe
)
{
	t_node_command	*cmd;

	if (node == NULL || node->type != NODE_COMMAND || node->content == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	cmd = (t_node_command *) node->content;
	exec_cmd_set_pipe_fds(cmd, fd[0], fd[1]);
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