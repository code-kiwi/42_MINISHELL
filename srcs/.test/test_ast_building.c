/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ast_building.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:25:37 by brappo            #+#    #+#             */
/*   Updated: 2024/04/11 09:17:45 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_ast_tree(t_node *node, int space);

// int	main(int argc, char **argv, char **envp)
// {
// 	t_minishell	shell;
// 	t_node		*ast_tree;

// 	t_minishell_init(&shell, argc, argv, envp);
// 	while (true)
// 	{
// 		shell.input = prompt(&shell);
// 		if (ft_strcmp(shell.input, "exit") == 0)
// 		{
// 			t_minishell_free(&shell);
// 			break ;
// 		}
// 		token_recognition(&shell);
// 		ast_tree = build_ast(shell.tokens);
// 		print_ast_tree(ast_tree, 0);
// 		printf("\n\n\n");
// 		ast_free(&ast_tree);
// 		ft_lstclear(&shell.tokens, t_token_free);
// 		add_history(shell.input);
// 		free(shell.input);
// 		shell.input = NULL;
// 	}
// 	exit(EXIT_SUCCESS);
// }

#define TEST_NUMBER 10

void	get_tests(char **tests)
{
	tests[0] = ft_strdup("echo 7 | echo 9");
	tests[1] = ft_strdup("echo 8");
	tests[2] = ft_strdup("");
	tests[3] = ft_strdup("(echo 8 || echo 9)");
	tests[4] = ft_strdup("<");
	tests[5] = ft_strdup("(echo)");
	tests[6] = ft_strdup("qwe | qwxe | qwxe| qwex| qwxe");
	tests[7] = ft_strdup("qwex && qex || qwex && qwex && qw xeq ex");
	tests[8] = ft_strdup("echo 7 < infile >> outfile");
	tests[9] = ft_strdup("< infile");
	// tests[10] = ft_strdup("()");
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	t_node		*ast_tree;
	char		*tests[TEST_NUMBER];
	size_t		index;

	t_minishell_init(&shell, argc, argv, envp);
	get_tests(tests);
	index = 0;
	while (index < TEST_NUMBER)
	{
		shell.input = tests[index];
		token_recognition(&shell);
		// ft_lstprint(shell.tokens, print_token);
		ast_tree = build_ast(shell.tokens);
		print_ast_tree(ast_tree, 0);
		printf("\n\n\n");
		ast_free(&ast_tree);
		ft_lstclear(&shell.tokens, t_token_free);
		if (index != TEST_NUMBER - 1)
			free(shell.input);
		index++;
	}
	t_minishell_free(&shell);
}