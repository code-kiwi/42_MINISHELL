/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_subshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:00:49 by brappo            #+#    #+#             */
/*   Updated: 2024/04/10 14:19:46 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_shell_end(t_list *tokens)
{
	t_token	*token;

	while (tokens->next != NULL)
	{
		token = (t_token *)tokens->content;
		if (token->type == OPERATOR_SHELL_CLOSE)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

bool	add_redirections_subshell(t_list **tokens, t_node *subshell)
{
	t_token	*token;

	if (tokens == NULL || *tokens == NULL)
		return (false);
	while (true)
	{
		token = (t_token *)(*tokens)->content;
		if (is_redirection(token->type))
		{
			if ((*tokens)->next == NULL)
				return (false);
			if (node_subshell_add_redirection(subshell, token->str,
					((t_token *)(*tokens)->next->content)->str) == false)
				return (false);
		}
		else
			break ;
		*tokens = (*tokens)->next;
	}
	return (true);
}

bool	add_subshell(t_node **current_node, t_node **head, t_list *tokens)
{
	t_list	*shell_end;
	t_list	*shell_end_next;
	t_node	*new_node;

	shell_end = get_shell_end(tokens);
	if (shell_end == NULL)
		return (false);
	shell_end_next = shell_end->next;
	shell_end->next = NULL;
	new_node = node_subshell_create(tokens);
	if (new_node == NULL)
	{
		shell_end->next = shell_end_next;
		return (false);
	}
	*current_node = new_node;
	if (*head == NULL)
		*head = new_node;
	if (add_redirections_subshell(&shell_end_next, new_node) == false)
	{
		shell_end->next = shell_end_next;
		node_subshell_free((void **)new_node);
		return (false);
	}
	return (get_nodes(current_node, head, shell_end_next));
}
