/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:14:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/28 13:27:20 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_tree_creation()
{
	// Test of AST creation
	t_node				*node;
	t_redirection_list	*redirections1;
	t_redirection_list	*redirections2;
	char				**argv1;
	int					argc1;
	char				**argv2;
	int					argc2;

	node = create_pipe_node();
	argc1 = 2;
	argc2 = 2;
	argv1 = (char **) ft_calloc((argc1 + 1), sizeof(char *));
	argv2 = (char **) ft_calloc((argc2 + 1), sizeof(char *));
	argv1[0] = ft_strdup("ls");
	argv1[1] = ft_strdup("-la");
	argv2[0] = ft_strdup("grep");
	argv2[1] = ft_strdup("\".txt\"");
	redirections1 = create_redirection_list();
	add_redirection(redirections1, ">>", "file1");
	add_redirection(redirections1, "<", "file2");
	add_redirection(redirections1, ">", "file3");
	add_redirection(redirections1, ">>", "file4");
	redirections2 = create_redirection_list();
	add_redirection(redirections2, ">>", "file5");
	add_redirection(redirections2, ">>", "file6");
	add_redirection(redirections2, ">>", "file7");
	add_redirection(redirections2, ">>", "file8");
	add_redirection(redirections2, ">>", "file9");
	node->child_left = create_command_node(argc1, argv1, redirections1);
	node->child_right = create_command_node(argc2, argv2, redirections2);

	while (getchar() != '\n');
	free_ast(&node);
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
