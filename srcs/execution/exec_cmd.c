/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:40:35 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/15 15:55:11 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Closes process' stdin and stdout
 *	Exits the process, frees the resources, prints the error message
 *	and returns the given status
 *	If cmd is provided, a special error handler for commands not found is called
 */
static void	exec_cmd_error(
	t_minishell *shell, char *err_msg, int status, char *cmd
)
{
	fd_close(STDIN_FILENO);
	fd_close(STDOUT_FILENO);
	if (cmd != NULL)
		handle_error_cmd(shell, err_msg, cmd);
	else
		handle_error(shell, err_msg, status);
}

/*
 *	Redirects process' stdin and stdout according to the command redirections
 *	In case of ERROR, the process exits after freeing all the resources
 *	and with an error status
 */
static void	exec_cmd_redirect(t_minishell *shell, t_node_command *cmd)
{
	if (
		shell == NULL || cmd == NULL || cmd->fd_in == FD_ERROR
		|| cmd->fd_out == FD_ERROR
	)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	if (cmd->fd_in != FD_UNSET)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			exec_cmd_error(shell, ERROR_MSG_CMD_REDIR, EXIT_FAILURE, NULL);
		fd_close_and_reset(&(cmd->fd_in));
	}
	if (cmd->fd_out != FD_UNSET)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			exec_cmd_error(shell, ERROR_MSG_CMD_REDIR, EXIT_FAILURE, NULL);
		fd_close_and_reset(&(cmd->fd_out));
	}
}

/*
 *	Executes an external command
 *	Steps:
 *		- Redirects process stdin and stdout according to command redirections
 *		- Finds the right path to the given command
 *		- Gets the shell's environment
 *		- Executes the command using execve()
 *	In case of ERROR, all the resources are freed and the process exits
 *	with the right status
 */
static void	exec_cmd_extrenal(t_minishell *shell, t_node_command *cmd)
{
	char	*command_path;
	char	**env;

	if (shell == NULL || cmd == NULL || !cmd->argv || cmd->argv[0] == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	exec_cmd_redirect(shell, cmd);
	command_path = exec_cmd_get_path(shell, (cmd->argv)[0]);
	if (command_path == NULL)
		exec_cmd_error(shell, ERROR_MSG_CMD_NFND, EXIT_FAILURE, (cmd->argv)[0]);
	env = env_get_all_array(shell->env);
	if (env == NULL)
	{
		free(command_path);
		exec_cmd_error(shell, ERROR_MSG_MEM, EXIT_FAILURE, NULL);
	}
	execve(command_path, cmd->argv, env);
	free(command_path);
	ft_free_str_array(&env);
	exec_cmd_error(shell, ERROR_MSG_CMD_EXEC, STATUS_CMD_NOT_EXEC, NULL);
}

/*
 *	Executes the given command into the given shell
 *	This function is only called from a child process
 *	If the command is a builtin:
 *		- we execute the builtin
 *		- we close the command file descriptors and free the shell ressources)
 *		- we exit the subprocess with the bultin returned status
 *	If we are with a command other than a builtin, exec_cmd_extrenal() is
 *	called
 */
void	exec_cmd(t_minishell *shell, t_node_command *cmd)
{
	int	returned_status;

	if (shell == NULL || cmd == NULL || !cmd->argv || cmd->argv[0] == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	if (is_built_in(cmd->argv[0]))
	{
		returned_status = exec_builtin(shell, cmd);
		node_command_close_fds(cmd);
		t_minishell_free(shell);
		exit(returned_status);
	}
	exec_cmd_extrenal(shell, cmd);
}
