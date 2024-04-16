/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execution1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:51:24 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/16 12:27:15 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ast_create(int nb);

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
// MAIN

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	int			status;
	int			chosen_test;

	if (argc != 2)
		handle_error(NULL, "INVALID ARGS FOR TESTING: please provide the test number", EXIT_FAILURE);
	chosen_test = ft_atoi(argv[1]);
	if (chosen_test < 1)
		handle_error(NULL, "INVALID ARGS FOR TESTING: invalid test number", EXIT_FAILURE);
	t_minishell_init(&shell, argc, argv, envp);

	shell.ast = ast_create(chosen_test);
	if (shell.ast == NULL)
		handle_error(&shell, "AST CREATION FAILED", EXIT_FAILURE);
	exec_ast(&shell);
	status = shell.status;
	t_minishell_free(&shell);
	return (status);
}
