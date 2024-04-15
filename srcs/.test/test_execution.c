/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:51:24 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/15 15:40:54 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ********************************************************************** */
// REDIRECTION_LIST UTILS

void	test_print_redirection(void *red)
{
	char			*op;
	t_redirection	*r;

	if (red == NULL)
		return ;
	r = (t_redirection *) red;
	op = "NONE";
	if (r->type == REDIRECTION_TYPE_HEREDOC)
		op = "<<";
	else if (r->type == REDIRECTION_TYPE_INFILE)
		op = "<";
	else if (r->type == REDIRECTION_TYPE_OUTFILE_TRUNC)
		op = ">";
	else if (r->type == REDIRECTION_TYPE_OUTFILE_APPEND)
		op = ">>";
	printf("\t- type: %s, filename: %s\n", op, r->filename);
}

void	test_print_redirection_list(t_redirection_list *red)
{
	if (red == NULL)
		printf("No redirection list...\n");
	printf("Redirection list:\n");
	ft_lstprint(red->redirections, test_print_redirection);
}

/* ********************************************************************** */
// NODE COMMAND UTILS

t_node	*node_cmd_create(char *cmd)
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

bool	node_cmd_add_redirs(t_node *node, char *op, char *filename)
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

void	node_cmd_print(t_node *node)
{
	t_node_command	*node_cmd;

	if (node == NULL || node->type != NODE_COMMAND || node->content == NULL)
	{
		errno = EINVAL;
		handle_error(NULL, "Impossible to print the COMMAND node", 0);
		return ;
	}
	node_cmd = (t_node_command *) node->content;
	printf("----------\n");
	printf("NODE COMMAND:\n");
	ft_print_str_array(node_cmd->argv);
	test_print_redirection_list(node_cmd->redirection_list);
}

/* ********************************************************************** */
// NODE PIPE UTILS

t_node	*node_pip_create(t_node *left, t_node *right)
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

/* ********************************************************************** */
// NODE LOGICAL UTILS

t_node	*node_and_create_test(t_node *left, t_node *right)
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

t_node	*node_or_create_test(t_node *left, t_node *right)
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


/* ********************************************************************** */
// T_MINISHELL UTILS
void	t_minishell_print(t_minishell *shell)
{
	t_pid_list	*current;

	if (shell == NULL)
	{
		printf("SHELL impossible to print...\n");
		return ;
	}
	printf("----------\n");
	printf("T_MINISHELL:\n");
	printf("Input: %s\n", shell->input);
	printf("Env:\n");
	ft_lstprint(shell->env, env_element_print);
	printf("Tokens:\n");
	ft_lstprint(shell->tokens, print_token);
	printf("Pids:\n");
	current = shell->pid_list;
	if (current == NULL)
		printf("Empty list of pids\n");
	else
	{
		while (current != NULL)
		{
			printf("PID %d\n", current->pid);
			current = current->next;
		}
	}
}

/* ********************************************************************** */
// AST_CREATION

/*
 *	Returns an AST for the command: "< Makefile cat | cat | cat > outfile"
 */
t_node	*ast_create1(void)
{
	t_node	*node_c1;
	t_node	*node_c2;
	t_node	*node_c3;
	t_node	*node_pipe1;
	t_node	*node_pipe2;

	// Creates node_c1
	node_c1 = node_cmd_create("cat");
	if (node_c1 == NULL)
		return (NULL);
	if (!node_cmd_add_redirs(node_c1, "<", "Makefile"))
		return (NULL);
	
	// Creates node_c2
	node_c2 = node_cmd_create("cat");
	if (node_c2 == NULL)
		return (NULL);

	// Creates node_c3
	node_c3 = node_cmd_create("cat");
	if (node_c3 == NULL)
		return (NULL);
	if (!node_cmd_add_redirs(node_c3, ">", "outfile"))
		return (NULL);

	// Creates pipe node
	node_pipe2 = node_pip_create(node_c2, node_c3);
	if (node_pipe2 == NULL)
		return (NULL);
	node_pipe1 = node_pip_create(node_c1, node_pipe2);
	if (node_pipe1 == NULL)
		return (NULL);
	return (node_pipe1);
}

/*
 *	Returns an AST for the command: "ls -la && sleep 5"
 */
t_node	*ast_create2(void)
{
	t_node	*node_c1;
	t_node	*node_c2;
	t_node	*node_and;

	// Creates node_c1
	node_c1 = node_cmd_create("ls -la");
	if (node_c1 == NULL)
		return (NULL);
	
	// Creates node_c2
	node_c2 = node_cmd_create("sleep 5");
	if (node_c2 == NULL)
		return (NULL);

	// Creates and node
	node_and = node_and_create_test(node_c1, node_c2);
	if (node_and == NULL)
		return (NULL);
	return (node_and);
}

/*
 *	Returns an AST for the command: "echo 1 | cat && echo 2"
 */
t_node	*ast_create3(void)
{
	t_node	*node_c1;
	t_node	*node_c2;
	t_node	*node_c3;
	t_node	*node_and;
	t_node	*node_pipe;

	// Creates node_c1
	node_c1 = node_cmd_create("echo 1");
	if (node_c1 == NULL)
		return (NULL);
	
	// Creates node_c2
	node_c2 = node_cmd_create("cat");
	if (node_c2 == NULL)
		return (NULL);

	// Creates node_c3
	node_c3 = node_cmd_create("ech 2");
	if (node_c3 == NULL)
		return (NULL);
	if (!node_cmd_add_redirs(node_c3, ">>", "outfile"))
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

/* ********************************************************************** */
// MAIN

#define NB_TESTS 3
int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	int			fd[2];
	int			status;
	int			chosen_test;

	if (argc != 2)
		handle_error(NULL, "INVALID ARGS FOR TESTING: please provide the test number", EXIT_FAILURE);
	chosen_test = ft_atoi(argv[1]);
	if (chosen_test < 1 && chosen_test > NB_TESTS)
		handle_error(NULL, "INVALID ARGS FOR TESTING: invalid test number", EXIT_FAILURE);
	t_minishell_init(&shell, argc, argv, envp);

	if (chosen_test == 1)
		shell.ast = ast_create1();
	else if (chosen_test == 2)
		shell.ast = ast_create2();
	else if (chosen_test == 3)
		shell.ast = ast_create3();

	if (shell.ast == NULL)
		handle_error(&shell, "AST CREATION FAILED", EXIT_FAILURE);
	fd[0] = FD_UNSET;
	fd[1] = FD_UNSET;
	exec_node(&shell, shell.ast, fd, false);

	t_minishell_get_exec_status(&shell);
	status = shell.status;
	t_minishell_free(&shell);
	return (status);
}
