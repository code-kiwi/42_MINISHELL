/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:39:46 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/10 16:57:22 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "minishell.h"
#include "node.h"

/*
 *	Executes the given command as a built_in function
 *	Steps:
 *		- checks args;
 *		- retrieves the correct built_in functions
 *		- selects the right fd_out to pass to the built_in function, in order
 *		to make it write to STDOUT or to the given command fd_out
 *		- calls the built_in function
 *	In case of ERROR prints an error messages and returns EXIT_FAILURE
 */
int	exec_builtin(t_minishell *shell, t_node_command *cmd)
{
	t_bi_func	bi_func;
	int			status;
	int			bi_fd_out;

	if (
		shell == NULL || cmd == NULL || cmd->argv == NULL
		|| cmd->argv[0] == NULL
	)
	{
		handle_error(NULL, ERROR_MSG_ARGS, 0);
		return (EXIT_FAILURE);
	}
	bi_func = built_in_get(shell->bi_funcs, cmd->argv[0]);
	if (bi_func == NULL)
	{
		handle_error(NULL, ERROR_MSG_WRONG_BI, 0);
		return (EXIT_FAILURE);
	}
	if (cmd->fd_out != FD_ERROR && cmd->fd_out != FD_UNSET)
		bi_fd_out = cmd->fd_out;
	else
		bi_fd_out = STDOUT_FILENO;
	status = bi_func(shell, cmd->argv, bi_fd_out);
	return (status);
}
