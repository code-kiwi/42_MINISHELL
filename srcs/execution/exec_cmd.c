/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:40:35 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/14 12:16:26 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd_error(t_minishell *shell, char *err_msg, int status)
{
	fd_close(STDIN_FILENO);
	fd_close(STDOUT_FILENO);
	handle_error(shell, err_msg, status);
}

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
			exec_cmd_error(shell, ERROR_MSG_CMD_REDIR, EXIT_FAILURE);
		fd_close_and_reset(&(cmd->fd_in));
	}
	if (cmd->fd_out != FD_UNSET)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			exec_cmd_error(shell, ERROR_MSG_CMD_REDIR, EXIT_FAILURE);
		fd_close_and_reset(&(cmd->fd_out));
	}
}

static void	exec_cmd_extrenal(t_minishell *shell, t_node_command *cmd)
{
	char	*command_path;
	char	**env;

	if (shell == NULL || cmd == NULL || !cmd->argv || cmd->argv[0] == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	exec_cmd_redirect(shell, cmd);
	command_path = exec_cmd_get_path(shell, (cmd->argv)[0]);
	printf("TEST: %s\n", command_path);
	if (command_path == NULL)
		exec_cmd_error(shell, ERROR_MSG_CMD_NOTFOUND, STATUS_CMD_NOT_FOUND);
	env = env_get_all_array(shell->env);
	if (env == NULL)
	{
		free(command_path);
		exec_cmd_error(shell, ERROR_MSG_MEM, STATUS_CMD_NOT_FOUND);
	}
	execve(command_path, cmd->argv, env);
	free(command_path);
	ft_free_str_array(&env);
	exec_cmd_error(shell, ERROR_MSG_CMD_EXEC, STATUS_CMD_NOT_EXEC);
}

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

