/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:24:53 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/28 13:26:12 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(t_minishell *shell, char *err_msg, int exit_status)
{
	if (shell != NULL)
		t_minishell_free(shell);
	if (errno != 0)
		ft_dprintf(STDERR_FILENO, "Error: %s: %s\n", err_msg, strerror(errno));
	else
		ft_dprintf(STDERR_FILENO, "Error: %s\n", err_msg);
	if (exit_status)
		exit(exit_status);
}
