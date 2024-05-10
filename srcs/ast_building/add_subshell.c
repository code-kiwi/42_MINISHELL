/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_subshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:00:49 by brappo            #+#    #+#             */
/*   Updated: 2024/05/10 16:55:51 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "node.h"
#include "build_ast.h"
#include "token.h"

static t_list	*get_shell_end(t_list *tokens)
{
	t_token	*token;
	size_t	shell_open_count;

	shell_open_count = 0;
	while (tokens->next != NULL)
	{
		token = (t_token *)tokens->next->content;
		if (token->type == OPERATOR_SHELL_OPEN)
			shell_open_count++;
		else if (token->type == OPERATOR_SHELL_CLOSE)
		{
			if (shell_open_count == 0)
				return (tokens);
			shell_open_count--;
		}
		tokens = tokens->next;
	}
	return (NULL);
}

static bool	add_redirections_subshell(t_list **tokens, t_node *subshell)
{
	t_token	*token;
	t_token	*next_token;

	if (tokens == NULL || *tokens == NULL)
		return (false);
	token = (*tokens)->content;
	while (is_redirection(token->type))
	{
		if ((*tokens)->next == NULL)
			return (false);
		next_token = (*tokens)->next->content;
		if (node_subshell_add_redirection(subshell, token->str,
				next_token->str) == false)
			return (false);
		*tokens = (*tokens)->next->next;
		token = (*tokens)->content;
	}
	return (true);
}

static t_list	*extract_subshell_tokens(t_list *tokens)
{
	t_list	*shell_end;
	t_list	*sub_tokens;
	t_list	*end_token_link;

	shell_end = get_shell_end(tokens);
	if (shell_end == NULL || tokens == shell_end)
	{
		ast_syntax_error(tokens->content);
		return (NULL);
	}
	end_token_link = get_end_token_list();
	if (end_token_link == NULL)
		return (NULL);
	sub_tokens = tokens->next;
	tokens->next = shell_end->next;
	shell_end->next = end_token_link;
	return (sub_tokens);
}

bool	add_subshell(t_node **current_node, t_node **head, t_list *tokens)
{
	t_list	*sub_tokens;
	t_node	*new_node;

	if (((t_token *)tokens->content)->type != OPERATOR_SHELL_OPEN
		|| current_node == NULL || head == NULL)
		return (false);
	if (*current_node != NULL)
		return (ast_syntax_error(tokens->content), false);
	sub_tokens = extract_subshell_tokens(tokens);
	if (sub_tokens == NULL)
		return (false);
	new_node = node_subshell_create(sub_tokens);
	if (new_node == NULL)
		return (ft_lstclear(&sub_tokens, t_token_free), false);
	if (!node_subshell_build_ast(new_node))
		return (node_free_single(&new_node), false);
	*current_node = new_node;
	if (*head == NULL)
		*head = new_node;
	tokens = tokens->next->next;
	if (add_redirections_subshell(&tokens, new_node) == false)
		return (false);
	return (get_nodes(current_node, head, tokens));
}
