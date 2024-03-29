/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:14:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/29 10:27:42 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_tree_creation()
{
	// Test of AST creation
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

int	main(void)
{
	t_minishell	shell;

	t_minishell_init(&shell);
	while (true)
	{
		shell.input = prompt();
		if (shell.input == NULL)
			handle_error(&shell, ERROR_MSG_PROMPT, EXIT_FAILURE);
		if (ft_strcmp(shell.input, "exit") == 0)
		{
			t_minishell_free(&shell);
			break ;
		}
		printf("%s\n", shell.input);
		free(shell.input);
		shell.input = NULL;

		//TEMP TEST
		test_tree_creation();
	}
	exit(EXIT_SUCCESS);
}
