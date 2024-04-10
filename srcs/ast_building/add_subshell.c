/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_subshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:00:49 by brappo            #+#    #+#             */
/*   Updated: 2024/04/10 12:47:00 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_shell_end(t_list *tokens)
{
	t_token	*token;

	while (tokens->next != NULL)
	{
		token = (t_token *)tokens->content;
		if (token->type == SHELL_CLOSE)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
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
	return (get_nodes(current_node, head, shell_end_next));
}
