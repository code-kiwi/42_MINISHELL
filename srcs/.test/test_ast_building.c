/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ast_building.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:25:37 by brappo            #+#    #+#             */
/*   Updated: 2024/04/10 15:16:40 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define COUNT 10

void	print_node_type(t_node_type	node_type)
{
	switch (node_type)
	{
		case NODE_COMMAND :
			printf("COMMAND");
			break ;
		case NODE_PIPE :
			printf("|");
			break ;
		case NODE_AND :
			printf("&&");
			break ;
		case NODE_OR :
			printf("||");
			break ;
		case NODE_SUBSHELL :
			printf("SUBSHELL");
			break ;
		default :
			printf("ERROR!!");
			break ;
	}
}

void print_ast_tree(t_node *node, int space)
{
    space += COUNT;
	if (node != NULL)
    	print_ast_tree(node->child_right, space);
    printf("\n");
    for (int i = COUNT; i < space; i++)
	{
        printf(" ");
	}
	if (node == NULL)
		printf("NULL");
	else
	{
    	print_node_type(node->type);
    	print_ast_tree(node->child_left, space);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	t_node		*ast_tree;

	t_minishell_init(&shell, argc, argv, envp);
	while (true)
	{
		shell.input = prompt(&shell);
		if (ft_strcmp(shell.input, "exit") == 0)
		{
			t_minishell_free(&shell);
			break ;
		}
		token_recognition(&shell);
		ast_tree = build_ast(shell.tokens);
		print_ast_tree(ast_tree, 0);
		printf("\n\n\n");
		ast_free(&ast_tree);
		ft_lstprint(shell.tokens, print_token);
		ft_lstclear(&shell.tokens, t_token_free);
		add_history(shell.input);
		free(shell.input);
		shell.input = NULL;
	}
	exit(EXIT_SUCCESS);
}