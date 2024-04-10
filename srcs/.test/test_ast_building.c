/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ast_building.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:25:37 by brappo            #+#    #+#             */
/*   Updated: 2024/04/10 16:53:57 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define COUNT 10

void	print_redireciton(enum e_redirection_type type)
{
	switch (type)
	{
		case REDIRECTION_TYPE_HEREDOC :
			printf("<<");
			break;
		case REDIRECTION_TYPE_INFILE :
			printf("<");
			break;
		case REDIRECTION_TYPE_OUTFILE_APPEND :
			printf(">>");
			break;
		case REDIRECTION_TYPE_OUTFILE_TRUNC :
			printf(">");
			break;
		default :
			printf("ERROR");
			break;
	}
}

void	print_cmd(t_node *node, int space)
{
	int				index;
	t_node_command	*cmd;
	t_list			*redirections;
	t_redirection	*redirection;

	index = 0;
	cmd = (t_node_command *)node->content;
	while (index <= cmd->argc)
	{
		printf("%s ", cmd->argv[index]);
		index++;
	}
	redirections = cmd->redirection_list->redirections;
	if (redirections == NULL)
		return ;
	printf("\n");
	for (int i = COUNT; i < space; i++)
	{
        printf(" ");
	}
	while (redirections != NULL)
	{
		redirection = redirections->content;
		print_redireciton(redirection->type);
		printf(" %s ", redirection->filename);
		redirections = redirections->next;
	}
}

int	count_cmd(t_node *node)
{
	int				index;
	t_node_command	*cmd;
	t_list			*redirections;
	t_redirection	*redirection;
	size_t			count;

	index = 0;
	count = 0;
	cmd = (t_node_command *)node->content;
	while (index <= cmd->argc)
	{
		count += ft_strlen(cmd->argv[index]);
		index++;
	}
	redirections = cmd->redirection_list->redirections;
	if (redirections == NULL)
		return (count);
	while (redirections != NULL)
	{
		redirection = redirections->content;
		count += ft_strlen(redirection->filename) + 2;
		redirections = redirections->next;
	}
	return (count);
}

void	print_node_type(t_node *node, int space)
{
	switch (node->type)
	{
		case NODE_COMMAND :
			print_cmd(node, space);
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

int	count_space(t_node *node)
{
	if (node == NULL)
		return (0);
	switch (node->type)
	{
		case NODE_COMMAND :
			return (count_cmd(node));
		default :
			return (0);
	}
	return (0);
}

void print_ast_tree(t_node *node, int space)
{
	int	additional_space;

    space += COUNT;
	additional_space = count_space(node);
	if (node != NULL)
    	print_ast_tree(node->child_right, space + additional_space);
    printf("\n");
    for (int i = COUNT; i < space; i++)
	{
        printf(" ");
	}
	if (node == NULL)
		printf("NULL");
	else
	{
    	print_node_type(node, space);
    	print_ast_tree(node->child_left, space + additional_space);
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
		// ft_lstprint(shell.tokens, print_token);
		// ft_lstclear(&shell.tokens, t_token_free);
		add_history(shell.input);
		free(shell.input);
		shell.input = NULL;
	}
	exit(EXIT_SUCCESS);
}