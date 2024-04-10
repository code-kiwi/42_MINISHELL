/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ast_creation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:46:10 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/10 11:14:21 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Creates an AST tree with t_node tools
 *	Tests the creation of pipe and command nodes
 *	Adds some redirections to the command nodes
 *	Frees the AST
 *
 *	! LEAKS on error
 *	! Just some dummy tests for the moment
 */
void	test_tree_creation(void)
{
	t_node				*node;
	t_node				*node_child_left;
	t_node				*node_child_right;
	char				**argv1;
	int					argc1;
	char				**argv2;
	int					argc2;

	node = node_pipe_create();
	if (node == NULL)
		handle_error(NULL, "Creating main pipe node impossible", EXIT_FAILURE);
	argc1 = 2;
	argc2 = 2;
	argv1 = (char **) ft_calloc((argc1 + 1), sizeof(char *));
	argv2 = (char **) ft_calloc((argc2 + 1), sizeof(char *));
	if (argv1 == NULL || argv2 == NULL)
		handle_error(NULL, "Creating argv impossible", EXIT_FAILURE);
	argv1[0] = ft_strdup("ls");
	argv1[1] = ft_strdup("-la");
	argv2[0] = ft_strdup("grep");
	argv2[1] = ft_strdup("\".txt\"");
	node->child_left = node_command_create(argc1, argv1);
	if (node->child_left == NULL)
		handle_error(NULL, "Creating child_left impossible", EXIT_FAILURE);
	node_child_left = node->child_left;
	node->child_right = node_command_create(argc2, argv2);
	if (node->child_right == NULL)
		handle_error(NULL, "Creating child_right impossible", EXIT_FAILURE);
	node_child_right = node->child_right;
	if (
		!node_command_add_redirection(node_child_left, ">>", "file1")
		|| !node_command_add_redirection(node_child_left, "<", "file2")
		|| !node_command_add_redirection(node_child_left, ">", "file3")
		|| !node_command_add_redirection(node_child_left, ">>", "file4")
	)
		handle_error(NULL, "Creating child_left's redirections impossible", EXIT_FAILURE);
	if (
		!node_command_add_redirection(node_child_right, ">>", "file5")
		|| !node_command_add_redirection(node_child_right, ">>", "file6")
		|| !node_command_add_redirection(node_child_right, ">>", "file7")
		|| !node_command_add_redirection(node_child_right, ">>", "file8")
		|| !node_command_add_redirection(node_child_right, ">>", "file9")
	)
		handle_error(NULL, "Creating child_right's redirections impossible", EXIT_FAILURE);
	while (getchar() != '\n');
	ast_free(&node);
}

void	test_tree_creation2(void)
{
	t_node	*node_and, *node_pipe1, *node_c1, *node_c2, *node_or, *node_pipe2, *node_c3, *node_c4, *node_sub;
	char	**argv1, **argv2, **argv3, **argv4;
	int		argc1, argc2, argc3, argc4;
	t_list	*token_list;

	// Creates basic nodes (and, or and pipe)
	node_and = node_and_create();
	node_or = node_or_create();
	node_pipe1 = node_pipe_create();
	node_pipe2 = node_pipe_create();
	
	// Creates command nodes
	argc1 = 2;
	argc2 = 2;
	argc3 = 2;
	argc4 = 2;
	argv1 = (char **) ft_calloc((argc1 + 1), sizeof(char *));
	argv2 = (char **) ft_calloc((argc2 + 1), sizeof(char *));
	argv3 = (char **) ft_calloc((argc3 + 1), sizeof(char *));
	argv4 = (char **) ft_calloc((argc4 + 1), sizeof(char *));
	argv1[0] = ft_strdup("ls");
	argv1[1] = ft_strdup("-la");
	argv2[0] = ft_strdup("grep");
	argv2[1] = ft_strdup("\".txt\"");
	argv3[0] = ft_strdup("ls");
	argv3[1] = ft_strdup("-la");
	argv4[0] = ft_strdup("grep");
	argv4[1] = ft_strdup("\".txt\"");
	node_c1 = node_command_create(argc1, argv1);
	node_c2 = node_command_create(argc2, argv2);
	node_c3 = node_command_create(argc3, argv3);
	node_c4 = node_command_create(argc4, argv4);
	if (
		!node_command_add_redirection(node_c1, ">>", "file1")
		|| !node_command_add_redirection(node_c1, "<", "file2")
		|| !node_command_add_redirection(node_c1, ">", "file3")
		|| !node_command_add_redirection(node_c1, ">>", "file4")
	)
		handle_error(NULL, "Creating node_c1's redirections impossible", EXIT_FAILURE);
	if (
		!node_command_add_redirection(node_c2, ">>", "file1")
		|| !node_command_add_redirection(node_c2, "<", "file2")
		|| !node_command_add_redirection(node_c2, ">", "file3")
		|| !node_command_add_redirection(node_c2, ">>", "file4")
	)
		handle_error(NULL, "Creating node_c2's redirections impossible", EXIT_FAILURE);
	if (
		!node_command_add_redirection(node_c3, ">>", "file1")
		|| !node_command_add_redirection(node_c3, "<", "file2")
		|| !node_command_add_redirection(node_c3, ">", "file3")
		|| !node_command_add_redirection(node_c3, ">>", "file4")
	)
		handle_error(NULL, "Creating node_c3's redirections impossible", EXIT_FAILURE);
	if (
		!node_command_add_redirection(node_c4, ">>", "file1")
		|| !node_command_add_redirection(node_c4, "<", "file2")
		|| !node_command_add_redirection(node_c4, ">", "file3")
		|| !node_command_add_redirection(node_c4, ">>", "file4")
	)
		handle_error(NULL, "Creating node_c4's redirections impossible", EXIT_FAILURE);

	// Creates subshell node
	t_minishell	shell;
	t_minishell_init(&shell, 0, NULL, NULL);
	shell.input = ft_strdup("echo -n bonjour");
	token_recognition(&shell);
	token_list = shell.tokens;
	node_sub = node_subshell_create(token_list);
	shell.tokens = NULL;
	free(shell.input);
	shell.input = NULL;
	if (
		!node_subshell_add_redirection(node_sub, ">>", "file1")
		|| !node_subshell_add_redirection(node_sub, "<", "file2")
		|| !node_subshell_add_redirection(node_sub, ">", "file3")
		|| !node_subshell_add_redirection(node_sub, ">>", "file4")
	)
		handle_error(NULL, "Creating node_sub's redirections impossible", EXIT_FAILURE);
	t_minishell_free(&shell);

	// Links all the nodes
	node_and->child_left = node_pipe1;
	node_and->child_right = node_or;
	node_pipe1->child_left = node_c1;
	node_pipe1->child_right = node_c2;
	node_or->child_left = node_pipe2;
	node_or->child_right = node_sub;
	node_pipe2->child_left = node_c3;
	node_pipe2->child_right = node_c4;
	while (getchar() != '\n');
	ast_free(&node_and);
}

int	main(void)
{
	test_tree_creation2();
	return (0);
}
