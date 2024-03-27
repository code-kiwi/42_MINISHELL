/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:24:53 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/27 13:31:53 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(t_minishell *shell, char *error_msg, int exit_status)
{
	if (shell != NULL)
		t_minishell_free(shell);
	if (errno != 0)
		ft_dprintf(STDERR_FILENO, "%s: %s\n", error_msg, strerror(errno));
	else
		ft_dprintf(STDERR_FILENO, "%s\n", error_msg);
	exit(exit_status);
}
