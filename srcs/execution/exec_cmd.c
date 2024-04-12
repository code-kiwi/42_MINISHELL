/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:40:35 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/12 15:46:31 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_minishell *shell, t_node_command *cmd)
{
	int	returned_status;

	if (shell == NULL || cmd == NULL || !cmd->argv || cmd->argv[0] == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	if (is_built_in(cmd->argv[0]))
	{
		returned_status = exec_builtin(shell, cmd);
		exit(returned_status);
	}
	node_command_close_fds(cmd);
	t_minishell_free(shell);
	exit(EXIT_SUCCESS);
}

