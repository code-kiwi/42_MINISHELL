/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:00:04 by brappo            #+#    #+#             */
/*   Updated: 2024/04/11 10:07:14 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirection(t_token_type token_type)
{
	return (token_type == OPERATOR_DGREAT
		|| token_type == OPERATOR_DLESS
		|| token_type == OPERATOR_GREAT
		|| token_type == OPERATOR_LESS);
}

bool	is_cmd_token(t_list *tokens)
{
	t_token	*token;

	if (tokens == NULL || tokens->content == NULL)
		return (false);
	token = (t_token *)tokens->content;
	return (token->type == WORD || is_redirection(token->type));
}

char	**get_argv(t_list *tokens)
{
	t_list	*argv;
	t_token	*token;
	char	**argv_array;

	argv = NULL;
	if (tokens == NULL)
		return (NULL);
	while (is_cmd_token(tokens))
	{
		token = (t_token *)tokens->content;
		if (is_redirection(token->type))
			tokens = tokens->next;
		else if (lst_push_front_content(&argv, ft_strdup(token->str)) == NULL)
		{
			ft_lstclear(&argv, free);
			return (NULL);
		}
		if (tokens != NULL)
			tokens = tokens->next;
	}
	ft_lstreverse(&argv);
	argv_array = (char **)to_array(argv);
	ft_lstclear(&argv, NULL);
	return (argv_array);
}

bool	add_redirections_command(t_list **tokens, t_node *cmd)
{
	t_token	*token;

	if (tokens == NULL || *tokens == NULL)
		return (false);
	while (is_cmd_token(*tokens))
	{
		token = (t_token *)(*tokens)->content;
		if (is_redirection(token->type))
		{
			if ((*tokens)->next == NULL)
				return (false);
			if (node_command_add_redirection(cmd, token->str,
					((t_token *)(*tokens)->next->content)->str) == false)
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
	if (new_node== NULL)
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
