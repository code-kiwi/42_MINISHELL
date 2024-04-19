/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:39:46 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/14 19:44:20 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Dummy function (temporary)
 */
int	exec_builtin(t_minishell *shell, t_node_command *cmd)
{
	if (shell || cmd)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
