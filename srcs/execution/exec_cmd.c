/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:40:35 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/13 18:09:19 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd_extrenal(t_minishell *shell, t_node_command *cmd)
{
	char	*command_path;
	char	**env;

	if (shell == NULL || cmd == NULL || !cmd->argv || cmd->argv[0] == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	exec_cmd_handle_redirections(shell, cmd);
	// ERROR HANDLING?
	command_path = exec_cmd_get_command_path(shell, (cmd->argv)[0]);
	if (command_path == NULL)
	{
		fd_close(STDIN_FILENO);
		fd_close(STDOUT_FILENO);
		handle_error(shell, ERROR_MSG_CMD_NOTFOUND, STATUS_CMD_NOT_FOUND);
	}
	env = env_get_all_array(shell->env);
	if (env == NULL)
	{
		fd_close(STDIN_FILENO);
		fd_close(STDOUT_FILENO);
		handle_error(shell, ERROR_MSG_CMD_NOTFOUND, STATUS_CMD_NOT_FOUND);
	}
	execve(command_path, cmd->argv, env);
	ft_free_str_array(&env);
	fd_close(STDIN_FILENO);
	fd_close(STDOUT_FILENO);
	handle_error(shell, ERROR_MSG_CMD_EXEC, STATUS_CMD_NOT_EXEC);
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

