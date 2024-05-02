/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:10:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/02 16:42:50 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "token.h"
#include "node.h"
#include "signals.h"
#include "pid_list.h"

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
 *	Given a pid, returns its exit status
 *	If the pid was exited by a signal, sets signal_handler to true
 *	If the pid is not valid, returns EXIT_FAILURE
 */
static int	get_return_value(pid_t pid, bool *signal_interruption)
{
	int	status;

	*signal_interruption = false;
	if (pid == PID_ERROR || waitpid(pid, &status, 0) == -1)
		return (EXIT_FAILURE);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		*signal_interruption = true;
		return (WTERMSIG(status) + 128);
	}
	return (EXIT_SUCCESS);
}

/*
 *	Returns true if one of the child process have been interrupted by a signal
 *	Sets the shell->status
 *	Clears the shell's pid_list member
 */
static bool	t_minishell_wait_pids(t_minishell *shell)
{
	t_pid_list	*current;
	bool		not_interrupted;
	bool		signal_interruption;

	if (shell == NULL)
		return (EXIT_FAILURE);
	current = shell->pid_list;
	not_interrupted = true;
	signal_interruption = false;
	while (current != NULL)
	{
		shell->status = get_return_value(current->pid, &signal_interruption);
		if (not_interrupted && signal_interruption)
			not_interrupted = false;
		current = current->next;
	}
	pid_list_clear(&(shell->pid_list));
	return (not_interrupted);
}

/*
 *	Returns if the childs haven been interrupted
 *	If the shell's pid list is empty, the current shell's status is returned
 */
bool	t_minishell_set_exec_status(t_minishell *shell)
{
	int		not_interrupted;
	size_t	nb_pids;

	if (shell == NULL)
		return (EXIT_FAILURE);
	nb_pids = pid_list_size(shell->pid_list);
	if (nb_pids == 0)
		return (shell->status);
	set_interactive_mode(false);
	not_interrupted = t_minishell_wait_pids(shell);
	if (not_interrupted == false)
	{
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			handle_error(shell, ERROR_MSG_WRITE, EXIT_FAILURE);
	}
	return (!not_interrupted);
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
