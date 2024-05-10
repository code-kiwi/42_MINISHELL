/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_node_subshell_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:07:01 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/10 16:55:24 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "minishell.h"
#include "build_ast.h"
#include "node.h"
#include "redirections.h"
#include "token.h"

/*
 *	Allocates a t_node with an allocated t_node_subshell as content.
 *	Returns a pointer to the t_node.
 *	The t_node children are set to NULL.
 *	The t_node_subshell token_list is set using the given token_list
 *	In case or ERROR, returns NULL
 */
t_node	*node_subshell_create(t_list *token_list)
{
	t_node			*node;
	t_node_subshell	*node_subshell;

	if (token_list == NULL)
		return (NULL);
	node = node_create_empty(NODE_SUBSHELL);
	if (node == NULL)
		return (NULL);
	node_subshell = (t_node_subshell *) ft_calloc(1, sizeof(t_node_subshell));
	if (node_subshell == NULL)
	{
		free(node);
		return (NULL);
	}
	node_subshell->token_list = token_list;
	node_subshell->ast = NULL;
	node_subshell->redirection_list = redirection_list_create();
	if (node_subshell->redirection_list == NULL)
	{
		free(node_subshell);
		free(node);
		return (NULL);
	}
	node->content = (void *) node_subshell;
	return (node);
}

/*
 *	Frees the memory allocated to a t_node_subshell
 *	Frees its token_list component
 *	Frees the redirections component
 *	Frees the t_node_subshell itself and sets the pointer to NULL
 */
void	node_subshell_free(void **node_ptr)
{
	t_node_subshell	*node;

	if (node_ptr == NULL || *node_ptr == NULL)
		return ;
	node = (t_node_subshell *) *node_ptr;
	ft_lstclear(&(node->token_list), t_token_free);
	if (node->ast != NULL)
		ast_free(&(node->ast));
	redirection_list_free(&(node->redirection_list));
	free(node);
	*node_ptr = NULL;
}

/*
 *	Adds a new redirection to a t_node of type NODE_SUBSHELL
 *	This node element has to be a t_node_subshell element (node type important)
 *	Returns true on SUCCESS
 *	Returns false on ERROR
 *	Error cases:
 *		- bad parameters given to the function
 *		- impossible to add a redirection
 */
bool	node_subshell_add_redirection(t_node *node, char *op, char *filename)
{
	t_node_subshell	*subshell;

	if (
		node == NULL || op == NULL || filename == NULL
		|| node->type != NODE_SUBSHELL || node->content == NULL
	)
		return (false);
	subshell = (t_node_subshell *) node->content;
	return (redirection_list_add(subshell->redirection_list, op, filename));
}

/*
 *	Builds the subshell node's AST based on its tokens field
 *	In case of ERROR, returns false, else returns true
 *	If the AST has not been built, an error message is displayed
 */
bool	node_subshell_build_ast(t_node *node)
{
	t_node_subshell	*node_sub;

	if (node == NULL || node->content == NULL || node->type != NODE_SUBSHELL)
		return (false);
	node_sub = (t_node_subshell *) node->content;
	node_sub->ast = build_ast(node_sub->token_list);
	if (node_sub->ast == NULL)
	{
		handle_error(NULL, ERROR_MSG_SUBAST, 0);
		return (false);
	}
	return (true);
}
