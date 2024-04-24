/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:00:04 by brappo            #+#    #+#             */
/*   Updated: 2024/04/12 09:26:50 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	add_redirections_command(t_list **tokens, t_node *cmd)
{
	t_token	*token;
	t_token	*next_token;

	if (tokens == NULL || *tokens == NULL)
		return (false);
	while (is_cmd_token(*tokens))
	{
		token = (t_token *)(*tokens)->content;
		if (is_redirection(token->type))
		{
			if ((*tokens)->next == NULL)
				return (false);
			next_token = (*tokens)->next->content;
			if (node_command_add_redirection(cmd, token->str,
					next_token->str) == false)
				return (false);
		}
		*tokens = (*tokens)->next;
	}
	return (true);
}

bool	add_command(t_node **current_node, t_node **head, t_list *tokens)
{
	t_node	*new_node;
	char	**argv;

	if (current_node == NULL || head == NULL
		|| *current_node != NULL)
		return (false);
	argv = get_argv(tokens);
	if (argv == NULL)
		return (false);
	new_node = node_command_create(array_size((void **)argv), argv);
	if (new_node == NULL)
	{
		ft_free_str_array(&argv);
		return (false);
	}
	if (*head == NULL)
		*head = new_node;
	*current_node = new_node;
	if (add_redirections_command(&tokens, new_node) == false)
		return (false);
	return (get_nodes(current_node, head, tokens));
}
