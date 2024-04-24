/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:11:52 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/24 16:41:59 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Handles an error of the echo command
 *	Displays the appropriate error message and returns the given status
 */
static int	bi_echo_handle_error(char *error_msg, int status)
{
	ft_dprintf(STDERR_FILENO, ECHO_MSG_LITERAL, error_msg);
	return (status);
}

/*
 *	Parses the given flag string in order to check if it contains the command
 *	handled flags
 *	Handled flags:
 *		- 'n': disables the new_line char appended to the result
 *		(if encountered, no_nl_mode is set to true, else it is set to false)
 *	If the flags string corresponds to a real flag, returns true, else returns
 *	false
 */
static bool	bi_echo_parse_flags(char *flags, bool *no_nl_mode)
{
	size_t	i;

	if (flags == NULL || no_nl_mode == NULL)
		return (false);
	*no_nl_mode = false;
	i = 0;
	if (flags[i] == '-')
	{
		i++;
		while (flags[i] == 'n')
			i++;
		if (i > 1 && ft_strlen(flags + i) == 0)
		{
			*no_nl_mode = true;
			return (true);
		}
	}
	return (false);
}

/*
 *	Displays a line of text composed of the elements from argv seperated by a
 *	space
 *	At the end of the line, displays a newline character, except if the first
 *	element of of argv contained the flag "-n"
 *	Returns EXIT_SUCCESS on SUCCESS, EXIT_FAILURE on ERROR
 *	NB: the argv[1] element is parsed in order to check is it corresponds to
 *	handled flags (if it does, the line prints elements starting from argv[2])
 *	ERROR cases:
 *		- call to ft_printf() fails;
 */
int	bi_echo(t_minishell *shell, char **argv)
{
	bool	no_nl_mode;
	size_t	i;

	if (shell == NULL || argv == NULL || argv[0] == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	i = 1;
	if (argv[i] == NULL)
	{
		if (ft_dprintf(STDOUT_FILENO, "\n") == -1)
			return (bi_echo_handle_error(ERROR_MSG_WRITE, EXIT_FAILURE));
		return (EXIT_SUCCESS);
	}
	if (bi_echo_parse_flags(argv[1], &no_nl_mode))
		i++;
	while (argv[i] != NULL)
	{
		if (ft_dprintf(STDOUT_FILENO, "%s", argv[i]) == -1)
			return (bi_echo_handle_error(ERROR_MSG_WRITE, EXIT_FAILURE));
		i++;
		if (argv[i] != NULL && ft_dprintf(STDOUT_FILENO, " ") == -1)
			return (bi_echo_handle_error(ERROR_MSG_WRITE, EXIT_FAILURE));
	}
	if (!no_nl_mode && ft_dprintf(STDOUT_FILENO, "\n") == -1)
		return (bi_echo_handle_error(ERROR_MSG_WRITE, EXIT_FAILURE));
	return (EXIT_SUCCESS);
}
