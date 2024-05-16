/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:40:35 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/16 13:35:11 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "libft.h"
#include "minishell.h"
#include "built_in.h"
#include "execution.h"
#include "node.h"
#include "env.h"
#include "expansion.h"

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
	if (err_msg != NULL && cmd != NULL)
		handle_error_cmd(shell, err_msg, cmd);
	else if (err_msg != NULL)
		handle_error(shell, err_msg, status);
	else
		handle_error(shell, NULL, status);
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
 *		- checks input args
 *		- stores cmd->argv into a local variable
 *		- frees the AST (this enables to close all the AST opened file
 *		descriptors)
 *		- executes the command calling execve()
 *		- frees the resources if execve() call failed (on SUCCESS, the program
 *		should never reach this step
 */
static void	exec_cmd_external_process(
	t_minishell *shell, t_node_command *cmd, char **env, char *command_path
)
{
	char	**argv;

	if (shell == NULL || cmd == NULL || env == NULL || command_path == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	argv = cmd->argv;
	cmd->argv = NULL;
	ast_free(&(shell->ast));
	execve(command_path, argv, env);
	ft_free_str_array(&argv);
	free(command_path);
	ft_free_str_array(&env);
	exec_cmd_error(shell, ERROR_MSG_CMD_EXEC, STATUS_CMD_NOT_EXEC, NULL);
}

/*
 *	Prepeares the execution of an external command
 *	Steps:
 *		- Redirects process stdin and stdout according to command's redirections
 *		- Finds the right path to the given command
 *		- Gets the shell's environment
 *		- Calls exec_cmd_external_process() in order to execute the command,
 *		handle properly resources and deal with errors
 *	In case of ERROR, all the resources are freed and the process exits
 *	with the right status
 */
static void	exec_cmd_external(t_minishell *shell, t_node_command *cmd)
{
	char	*cmd_path;
	char	**env;
	int		status;

	if (shell == NULL || cmd == NULL || !cmd->argv || cmd->argv[0] == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	status = 0;
	exec_cmd_redirect(shell, cmd);
	cmd_path = exec_cmd_get_path(shell, (cmd->argv)[0], &status);
	if (cmd_path == NULL)
		exec_cmd_error(shell, ERROR_MSG_CMD_NFND, EXIT_FAILURE, (cmd->argv)[0]);
	if (status == STATUS_CMD_NOT_EXEC)
	{
		if (ft_strchr((cmd->argv)[0], '/') != NULL && path_is_dir(cmd_path))
			ft_dprintf(STDERR_FILENO, ERROR_TEMPL, cmd_path, ERROR_MSG_CMD_DIR);
		else
			ft_dprintf(STDERR_FILENO, ERROR_TEMPL, cmd_path, ERROR_MSG_CMD_PRM);
		free(cmd_path);
		exec_cmd_error(shell, NULL, STATUS_CMD_NOT_EXEC, NULL);
	}
	env = env_get_all_array(shell->env, false);
	if (env != NULL)
		return (exec_cmd_external_process(shell, cmd, env, cmd_path));
	free(cmd_path);
	exec_cmd_error(shell, ERROR_MSG_MEM, EXIT_FAILURE, NULL);
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

	if (shell == NULL || cmd == NULL || !cmd->argv)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	if (is_built_in(shell->bi_funcs, cmd->argv[0]))
	{
		returned_status = exec_builtin(shell, cmd);
		node_command_close_fds(cmd);
		t_minishell_free(shell);
		exit(returned_status);
	}
	exec_cmd_external(shell, cmd);
}
