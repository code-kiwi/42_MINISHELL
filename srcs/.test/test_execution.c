/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:51:24 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/15 02:30:06 by mhotting         ###   ########.fr       */
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

bool	node_cmd_add_redirs1(t_node *node)
{
	if (node == NULL || node->type != NODE_COMMAND)
	{
		errno = EINVAL;
		handle_error(NULL, "Impossible to create cmd node", 0);
		return (false);
	}
	if (
		!node_command_add_redirection(node, "<", "Makefile")
		//|| !node_command_add_redirection(node, "<", "file2")
		//|| !node_command_add_redirection(node, "<<", "LIM2")
	)
	{
		handle_error(NULL, "Creating node's redirections impossible", 0);
		return (false);
	}
	return (true);
}

bool	node_cmd_add_redirs2(t_node *node)
{
	if (node == NULL || node->type != NODE_COMMAND)
	{
		errno = EINVAL;
		handle_error(NULL, "Impossible to create cmd node", 0);
		return (false);
	}
	if (
		!node_command_add_redirection(node, ">>", "file4")
		|| !node_command_add_redirection(node, ">", "file3")
	)
	{
		handle_error(NULL, "Creating node's redirections impossible", 0);
		return (false);
	}
	return (true);
}

bool	node_cmd_add_redirs3(t_node *node)
{
	if (node == NULL || node->type != NODE_COMMAND)
	{
		errno = EINVAL;
		handle_error(NULL, "Impossible to create cmd node", 0);
		return (false);
	}
	if (
		//!node_command_add_redirection(node, ">>", "file4")
		!node_command_add_redirection(node, ">>", "file3")
	)
	{
		handle_error(NULL, "Creating node's redirections impossible", 0);
		return (false);
	}
	return (true);
}

/* ********************************************************************** */
// NODE PIPE UTILS

t_node	*node_pip_create(t_node *left, t_node *right)
{
	t_node	*node_pipe;

	node_pipe = node_pipe_create();
	if (node_pipe == NULL)
	{
		handle_error(NULL, "Impossible to create pipe node", 0);
		return (NULL);
	}
	node_pipe->child_left = left;
	node_pipe->child_right = right;
	return (node_pipe);
}


void	node_cmd_print(t_node *node)
{
	t_node_command	*node_cmd;

	if (node == NULL || node->type != NODE_COMMAND || node->content == NULL)
	{
		errno = EINVAL;
		handle_error(NULL, "Impossible to print the cmd node", 0);
		return ;
	}
	node_cmd = (t_node_command *) node->content;
	printf("----------\n");
	printf("NODE COMMAND:\n");
	ft_print_str_array(node_cmd->argv);
	test_print_redirection_list(node_cmd->redirection_list);
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
// MAIN

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	t_node		*node_c1;
	t_node		*node_c2;
	t_node		*node_c3;
	t_node		*node_pipe1;
	t_node		*node_pipe2;
	int			fd[2];
	int			status;

	t_minishell_init(&shell, argc, argv, envp);
	//t_minishell_print(&shell);
	//t_minishell_print(&shell);
	
	// Creates node_c1
	node_c1 = node_cmd_create("cat");
	if (node_c1 == NULL)
		exit(EXIT_FAILURE);
	if (!node_cmd_add_redirs1(node_c1))
		exit(EXIT_FAILURE);
	//node_cmd_print(node_c1);
	
	// Creates node_c2
	node_c2 = node_cmd_create("cat");
	if (node_c2 == NULL)
		exit(EXIT_FAILURE);
	//if (!node_cmd_add_redirs2(node_c2))
	//	exit(EXIT_FAILURE);
	//node_cmd_print(node_c2);

	// Creates node_c3
	node_c3 = node_cmd_create("cat");
	if (node_c3 == NULL)
		exit(EXIT_FAILURE);
	if (!node_cmd_add_redirs3(node_c3))
		exit(EXIT_FAILURE);
	//node_cmd_print(node_c3);

	// Creates pipe node
	node_pipe2 = node_pip_create(node_c2, node_c3);
	if (node_pipe2 == NULL)
		exit(EXIT_FAILURE);
	node_pipe1 = node_pip_create(node_c1, node_pipe2);
	if (node_pipe1 == NULL)
		exit(EXIT_FAILURE);

	shell.ast = node_pipe1;
	fd[0] = FD_UNSET;
	fd[1] = FD_UNSET;
	exec_node(&shell, shell.ast, fd, false);

	status = t_minishell_wait_pids(&shell);
	printf("Status: %d\n", status);

	t_minishell_free(&shell);
	return (status);
}
