/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:24:53 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/07 21:04:57 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "libft.h"
#include "minishell.h"

/*
 *	Handles errors while running the program
 *	If a t_minishell data is given, it frees all the memory used by it
 *	An error message can be provided
 *	If errno is not 0, the corresponding errno string is printed
 *	If the exit status provided corresponds to an error status,
 *	the program exits
 */
void	handle_error(t_minishell *shell, char *err, int exit_status)
{
	if (shell != NULL)
		t_minishell_free(shell);
	if (err != NULL)
	{
		if (errno != 0)
			ft_dprintf(STDERR_FILENO, "Minishell: %s: %s\n", err, \
				strerror(errno));
		else
			ft_dprintf(STDERR_FILENO, "Minishell: %s\n", err);
	}
	if (exit_status)
		exit(exit_status);
}

/*
 *	Handles errors onnly for unexisting command errors
 *	This error is formatted differently than the other erros
 *	If a t_minishell data is given, it frees all the memory used by it
 *	An error message can be provided
 *	If the exit status provided corresponds to an error status,
 *	the program exits
 */
void	handle_error_cmd(t_minishell *shell, char *err_msg, char *cmd)
{
	ft_dprintf(STDERR_FILENO, "Minishell: %s: %s\n", err_msg, cmd);
	if (shell != NULL)
		t_minishell_free(shell);
	exit(STATUS_CMD_NOT_FOUND);
}
