/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:24:53 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/29 10:59:15 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Handles errors while running the program
 *	If a t_minishell data is given, it frees all the memory used by it
 *	An error message can be provided
 *	If errno is not 0, the corresponding errno string is printed
 *	If the exit status provided corresponds to an error status,
 *	the program exits
 */
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
