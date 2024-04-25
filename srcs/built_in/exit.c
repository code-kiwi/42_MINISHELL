/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:03:49 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/25 12:43:54 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"
#include "minishell.h"
#include "built_in.h"

/*
 *	Exits the current shell process with the given status and prompting the
 *	appropriate message onto stderr
 *	Frees the resources used by the given shell
 */
static void	bi_exit_shell(t_minishell *shell, int status, char *msg)
{
	if (status == STATUS_EXIT_BAD_ARG)
		ft_dprintf(STDERR_FILENO, EXIT_MSG_ARG_NON_NUM, msg);
	else
		ft_dprintf(STDERR_FILENO, MSG_LITERAL, msg);
	if (shell != NULL)
		t_minishell_free(shell);
	exit(status);
}

/*
 *	Checks is the given string is a valid exit status
 *	Returns true if str is valid, else returns false
 *	STATUS is valid if it is numeric and if LONG_MIN <= STATUS <= LONG_MAX
 */
static bool	bi_exit_is_numeric(char *str)
{
	char			*ptr;
	int				sign;
	unsigned long	nb;

	sign = 1;
	if (str == NULL || *str == '\0')
		return (false);
	ptr = str;
	while (ft_isspace(*ptr))
		ptr++;
	if ((*ptr == '+' || *ptr == '-') && *(ptr++) == '-')
		sign = -1;
	while (*ptr == '0')
		ptr++;
	if (ft_strlen(ptr) > 19)
		return (false);
	nb = ft_atoul(ptr);
	while (ft_isdigit(*ptr))
		ptr++;
	if (ft_strlen(ptr) != 0)
		return (false);
	if ((sign == 1 && nb > LONG_MAX) || (sign == -1 && nb - 1 > LONG_MAX))
		return (false);
	return (true);
}

/*
 *	Exits the current shell process
 *	Format "exit <STATUS>" stored into the given argv NULL terminated array
 *	Principles:
 *		- if STATUS is not provided, exits with EXIT_SUCCESS status while
 *		freeing all the resources and prompting a message onto stderr
 *		- if STATUS is provided and a valid status, exits with the given STATUS
 *		while freeing all the resources and prompting a message onto stderr
 *		- if STATUS is invalid, exits with the appropriate error status, freeing
 *		the resources and prompting an error message onto stderr
 *		- if more args are given, does not exit, prompts an error message and
 *		does not stop the current shell process
 */
int	bi_exit(t_minishell *shell, char **argv)
{
	if (shell == NULL || argv == NULL || argv[0] == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	if (argv[1] == NULL)
		bi_exit_shell(shell, EXIT_SUCCESS, EXIT_MSG_BASIC);
	if (!bi_exit_is_numeric(argv[1]))
		bi_exit_shell(shell, STATUS_EXIT_BAD_ARG, argv[1]);
	if (argv[2] != NULL)
	{
		ft_dprintf(STDERR_FILENO, MSG_LITERAL, EXIT_MSG_TOO_MANY_ARGS);
		return (EXIT_FAILURE);
	}
	bi_exit_shell(shell, (unsigned char)ft_atol(argv[1]), EXIT_MSG_BASIC);
	return (0);
}
