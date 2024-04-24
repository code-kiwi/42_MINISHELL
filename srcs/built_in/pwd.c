/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:10:53 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/24 17:09:41 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_pwd(t_minishell *shell, char **argv)
{
	char	*curr_dir;

	// ADD the use of env!
	if (shell == NULL || argv == NULL || argv[0] == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	curr_dir = getcwd(NULL, 0);
	if (curr_dir == NULL)
	{
		ft_dprintf(STDERR_FILENO, MSG_LITERAL, PWD_MSG_ERROR);
		return (EXIT_FAILURE);
	}
	ft_printf(MSG_LITERAL, curr_dir);
	free(curr_dir);
	return (EXIT_SUCCESS);
}
