/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_printing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 08:39:38 by brappo            #+#    #+#             */
/*   Updated: 2024/04/26 16:11:02 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "redirections.h"
#include "node.h"
#include "token.h"

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

void	print_subshell(t_node *node, int space)
{
	t_node_subshell	*subshell;
	t_list			*tokens;
	t_token			*token;
	t_list			*redirections;
	t_redirection	*redirection;

	subshell = node->content;
	tokens = subshell->token_list;
	redirections = subshell->redirection_list->redirections;
	printf("\n");
	for (int i = COUNT; i < space; i++)
	{
        printf(" ");
	}
	printf("SUBSHELL : ");
	while (tokens != NULL)
	{
		token = tokens->content;
		print_token((void *)token);
		if (tokens->next != NULL)
			printf(" -> ");
		tokens = tokens->next;
	}
	printf("\n");
	while (redirections != NULL)
	{
		redirection = redirections->content;
		print_redireciton(redirection->type);
		printf(" %s ", redirection->filename);
		redirections = redirections->next;
	}
}

size_t	count_subshell(t_node *node)
{
	t_node_subshell	*subshell;
	t_list			*tokens;
	t_token			*token;
	size_t			count;

	subshell = node->content;
	tokens = subshell->token_list;
	count = 0;
	while (tokens != NULL)
	{
		token = tokens->content;
		count += ft_strlen(token->str) + 12;
		tokens = tokens->next;
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
			print_subshell(node, space);
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
		case NODE_SUBSHELL :
			return (count_subshell(node));
		default :
			return (0);
	}
	return (0);
}

void print_ast_tree(t_node *node, int space)
{
	int	additional_space;

	if (node == NULL)
	{
		if (space == 0)
			printf("\nNULL");
		return ;
	}
    space += COUNT;
	additional_space = count_space(node);
    print_ast_tree(node->child_right, space + additional_space);
    printf("\n");
    for (int i = COUNT; i < space; i++)
	{
        printf(" ");
	}
    print_node_type(node, space);
    print_ast_tree(node->child_left, space + additional_space);
}
