/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node_subshell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:52:21 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/17 13:42:25 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ********************************************************************** */
// TEMPORARY CODE
static t_node	*node_cmd_create(char *cmd)
{
	t_node	*node;
	int		argc;
	char	**argv;

	argv = ft_split(cmd, " ");
	if (argv == NULL)
	{
		handle_error(NULL, "Impossible to create cmd node", 0);
		return (NULL);
	}
	argc = 0;
	while (argv[argc] != NULL)
		argc++;
	node = node_command_create(argc, argv);
	if (node == NULL)
	{
		handle_error(NULL, "Impossible to create cmd node", 0);
		ft_free_str_array(&argv);
		return (NULL);
	}
	return (node);
}

static bool	node_cmd_add_redirs(t_node *node, char *op, char *filename)
{
	if (node == NULL || node->type != NODE_COMMAND)
	{
		errno = EINVAL;
		handle_error(NULL, "Impossible to create cmd node", 0);
		return (false);
	}
	if (!node_command_add_redirection(node, op, filename))
	{
		handle_error(NULL, "Creating node's redirections impossible", 0);
		return (false);
	}
	return (true);
}

static t_node	*node_pip_create(t_node *left, t_node *right)
{
	t_node	*node_pipe;

	node_pipe = node_pipe_create();
	if (node_pipe == NULL)
	{
		handle_error(NULL, "Impossible to create PIPE node", 0);
		return (NULL);
	}
	node_pipe->child_left = left;
	node_pipe->child_right = right;
	return (node_pipe);
}

static t_node	*node_and_create_test(t_node *left, t_node *right)
{
	t_node	*node_and;

	node_and = node_and_create();
	if (node_and == NULL)
	{
		handle_error(NULL, "Impossible to create AND node", 0);
		return (NULL);
	}
	node_and->child_left = left;
	node_and->child_right = right;
	return (node_and);
}

/*
static t_node	*node_or_create_test(t_node *left, t_node *right)
{
	t_node	*node_or;

	node_or = node_or_create();
	if (node_or == NULL)
	{
		handle_error(NULL, "Impossible to create OR node", 0);
		return (NULL);
	}
	node_or->child_left = left;
	node_or->child_right = right;
	return (node_or);
}
*/

static t_node	*TEMP_build_ast(t_list	*token_list)
{
	t_node	*node_c1;
	t_node	*node_c2;
	t_node	*node_c3;
	t_node	*node_and;
	t_node	*node_pipe;
	(void) token_list;

	// Creates node_c1
	node_c1 = node_cmd_create("cat");
	if (node_c1 == NULL)
		return (NULL);
	if (!node_cmd_add_redirs(node_c1, ">", "outfile"))
		return (NULL);

	// Creates node_c2
	node_c2 = node_cmd_create("echo 13");
	if (node_c2 == NULL)
		return (NULL);

	// Creates node_c3
	node_c3 = node_cmd_create("echo 23");
	if (node_c3 == NULL)
		return (NULL);
	if (!node_cmd_add_redirs(node_c3, ">", "outfile2"))
		return (NULL);

	// Creates pipe node
	node_pipe = node_pip_create(node_c1, node_c2);
	if (node_pipe == NULL)
		return (NULL);

	// Creates and node
	node_and = node_and_create_test(node_pipe, node_c3);
	if (node_and == NULL)
		return (NULL);
	return (node_and);
}

// END TEMPORARY CODE
/* ********************************************************************** */

/*
 *	Frees the memory, closes the given fds and exits the program with error
 *	status
 *	NB: Freeing the given shell will free its parent shells recursively
 */
static void	exec_subshell_error(t_minishell *shell, int fds[2])
{
	exec_node_close_fds(fds);
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
	fds[0] = FD_UNSET;
	fds[1] = FD_UNSET;
}

/*
 *	Stores the final node_subshell redirections into fds_subshell
 *	The given fds values will be given to fds_subshell
 *	Then we execute the node_subshell redirections and if they lead to valid
 *	files descriptors, they will overwrite the previous ones
 *	NB: when overwriting, the previous fds are closed in order to avoid fd leaks
 */
static void	exec_subshell_set_fds(
	t_node_subshell *node_sub, int fds[2], int fds_subshell[2]
)
{
	t_redirection_list	*red;

	exec_subshell_set_fds_initial(fds, fds_subshell);
	if (node_sub == NULL || node_sub->redirection_list == NULL)
		return ;
	red = node_sub->redirection_list;
	exec_redirection_list(red);
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
 *		- the AST is evaluated according to the node's token_list
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
	exec_subshell_set_fds(node_sub, fds, fds_subshell);
	if (fds_subshell[0] == FD_ERROR || fds_subshell[1] == FD_ERROR)
		exec_subshell_error(&subshell, fds_subshell);
	subshell.ast = TEMP_build_ast(node_sub->token_list);
	if (subshell.ast == NULL)
		exec_subshell_error(&subshell, fds_subshell);
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
	exec_node_close_fds(fds);
}
