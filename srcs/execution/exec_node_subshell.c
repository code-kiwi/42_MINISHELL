/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node_subshell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:52:21 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/10 16:57:47 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "minishell.h"
#include "execution.h"
#include "node.h"
#include "redirections.h"
#include "build_ast.h"

/*
 *	Frees the memory, closes the given fds and exits the program with error
 *	status
 *	NB: Freeing the given shell will free its parent shells recursively
 */
static void	exec_subshell_error(t_minishell *shell, int fds[2])
{
	fds_close_and_reset(fds);
	t_minishell_free(shell);
	exit(EXIT_FAILURE);
}

/*
 *	Sets fds_subshells members to the values of fds members, setting those ones
 *	to FD_UNSET value
 */
static void	exec_subshell_set_fds_initial(int fds[2], int fds_subshell[2])
{
	fds_subshell[0] = fds[0];
	fds_subshell[1] = fds[1];
	fds_init(fds);
}

/*
 *	Stores the final node_subshell redirections into fds_subshell
 *	The given fds values will be given to fds_subshell
 *	Then we execute the node_subshell redirections and if they lead to valid
 *	files descriptors, they will overwrite the previous ones
 *	NB: when overwriting, the previous fds are closed in order to avoid fd leaks
 */
static void	exec_subshell_set_fds(
	t_minishell *shell, t_node_subshell *node_sub, int fds[2],
	int fds_subshell[2]
)
{
	t_redirection_list	*red;

	exec_subshell_set_fds_initial(fds, fds_subshell);
	if (node_sub == NULL || node_sub->redirection_list == NULL)
		return ;
	red = node_sub->redirection_list;
	exec_redirection_list(shell, red);
	if (red->info.fd_stdin != FD_UNSET)
	{
		if (fds_subshell[0] != FD_UNSET)
			fd_close_and_reset(&(fds_subshell[0]));
		fds_subshell[0] = red->info.fd_stdin;
		red->info.fd_stdin = FD_UNSET;
	}
	if (red->info.fd_stdout != FD_UNSET)
	{
		if (fds_subshell[1] != FD_UNSET)
			fd_close_and_reset(&(fds_subshell[1]));
		fds_subshell[1] = red->info.fd_stdout;
		red->info.fd_stdout = FD_UNSET;
	}
}

/*
 *	Process the execution of the given subshell node
 *	Supposed to be called from a subprocess of the shell main's process
 *	Steps:
 *		- a new instance of t_minishell is created in order to have a fresh
 *		list of pids, corresponding to the subshell ones
 *		- the redirections are performed
 *		- the subshell's AST is taken from node_subshell (the node_subshell ast
 *		member is then set to NULL
 *		- the AST is executed
 *		- resources are freed and the process exits with the subshell status
 *	NB: we do not need to free the given node because it is a part of the AST
 *	stored into mainshell->ast member
 */
static void	exec_subshell(t_minishell *mainshell, t_node *node, int fds[2])
{
	t_minishell		subshell;
	int				fds_subshell[2];
	int				status;
	t_node_subshell	*node_sub;

	if (
		mainshell == NULL || node == NULL || node->content == NULL
		|| fds[0] == FD_ERROR || fds[1] == FD_ERROR
	)
		exec_subshell_error(mainshell, fds);
	node_sub = (t_node_subshell *) node->content;
	t_minishell_init_subshell(&subshell, mainshell);
	exec_subshell_set_fds(mainshell, node_sub, fds, fds_subshell);
	if (fds_subshell[0] == FD_ERROR || fds_subshell[1] == FD_ERROR)
		exec_subshell_error(&subshell, fds_subshell);
	if (node_sub->ast == NULL)
		exec_subshell_error(&subshell, fds_subshell);
	subshell.ast = node_sub->ast;
	node_sub->ast = NULL;
	exec_ast(&subshell, fds_subshell);
	status = subshell.status;
	t_minishell_free(&subshell);
	exit(status);
}

/*
 *	Prepares the execution of the given subshell node
 *	Steps:
 *		- forks in order to do the subshell execution into a child process
 *		- in the child process lauches the execution
 *		- in the parent process, adds the subprocess' pid to the
 *		shell's pid list
 *	NB: The given fds are closed in order to avoid fd leaks, but this does not
 *	close them for the child process
 */
void	exec_node_subshell(t_minishell *shell, t_node *node, int fds[2])
{
	pid_t			pid;

	if (node == NULL || node->type != NODE_SUBSHELL || node->content == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		handle_error(shell, ERROR_MSG_FORK, EXIT_FAILURE);
	if (pid == 0)
	{
		shell->is_child_process = true;
		exec_subshell(shell, node, fds);
	}
	if (!t_minishell_add_pid(shell, pid))
		handle_error(shell, ERROR_MSG_MEM, EXIT_FAILURE);
	fds_close_and_reset(fds);
}
