/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:10:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/02 02:35:02 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/wait.h>
#include "libft.h"
#include "minishell.h"
#include "pid_list.h"
#include "token.h"
#include "node.h"

/*
 *	Adds a pid to the given shell's pid list
 *	Returns true on SUCCESS, false on ERROR
 */
bool	t_minishell_add_pid(t_minishell *shell, pid_t pid)
{
	t_pid_list	*new;

	if (shell == NULL)
	{
		errno = EINVAL;
		return (false);
	}
	new = pid_list_new(pid);
	if (new == NULL)
		return (false);
	pid_list_add_back(&(shell->pid_list), new);
	return (true);
}

/*
 *	Returns the status from the execution of the process whose pid was saved
 *	into the shell's pid_list member
 *	Clears the shell's pid_list member
 *	If the list is empty, returns EXIT_SUCCESS as a default value
 */
static int	t_minishell_wait_pids(t_minishell *shell)
{
	t_pid_list	*current;
	int			ret;
	int			status;

	if (shell == NULL)
		return (EXIT_FAILURE);
	current = shell->pid_list;
	ret = EXIT_SUCCESS;
	while (current != NULL)
	{
		if (current->pid == PID_ERROR && current->next == NULL)
			ret = EXIT_FAILURE;
		else if (current->pid != PID_ERROR)
		{
			if (waitpid(current->pid, &status, 0) == -1)
				ret = EXIT_FAILURE;
			if (ret == 0 && current->next == NULL && !WIFEXITED(status))
				ret = WEXITSTATUS(status);
			else if (ret == 0 && current->next == NULL && WEXITSTATUS(status))
				ret = WEXITSTATUS(status);
		}
		current = current->next;
	}
	pid_list_clear(&(shell->pid_list));
	return (ret);
}

/*
 *	Returns the shell's current status (by checking all the subprocess'
 *	execution status)
 *	If the shell's pid list is empty, the current shell's status is returned
 */
int	t_minishell_get_exec_status(t_minishell *shell)
{
	int		status;
	size_t	nb_pids;

	if (shell == NULL)
		return (EXIT_FAILURE);
	nb_pids = pid_list_size(shell->pid_list);
	if (nb_pids == 0)
		return (shell->status);
	status = t_minishell_wait_pids(shell);
	shell->status = status;
	return (status);
}

/*
 *	Resets the given shell
 *	Steps:
 *		- checks the given shell arg
 *		- clears the shell's token list
 *		- clears the shell's AST
 *		- clears the shell's input
 *	In case of ERROR (wrong arg), closes the current shell displaying an error
 *	message.
 */
void	utils_reset_shell(t_minishell *shell)
{
	if (shell == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	ft_lstclear(&shell->tokens, t_token_free);
	ast_free(&(shell->ast));
	free(shell->input);
	shell->input = NULL;
}

/*
 *	Handles an empty command for the given shell
 *	Steps:
 *		- checks the given shell arg
 *		- resets the shell
 *		- sets the shell status to zero
 *	In case of ERROR (wrong arg), closes the current shell displaying an error
 *	message.
 */
void	utils_handle_empty_cmd(t_minishell *shell)
{
	if (shell == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	utils_reset_shell(shell);
	shell->status = 0;
}
