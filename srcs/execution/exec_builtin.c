/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:39:46 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/24 13:46:57 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Dummy function (temporary)
 */
int	exec_builtin(t_minishell *shell, t_node_command *cmd)
{
	t_bi_func	bi_func;

	if (shell == NULL || cmd == NULL || cmd->argv == NULL || cmd->argv[0] == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	bi_func = built_in_get(shell->bi_funcs, cmd->argv[0]);
	if (bi_func == NULL)
		handle_error(shell, ERROR_MSG_WRONG_BI, EXIT_FAILURE);
	return (bi_func(shell, cmd->argv));
}
