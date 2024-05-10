/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:14:38 by brappo            #+#    #+#             */
/*   Updated: 2024/05/10 16:55:56 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "libft.h"
#include "minishell.h"
#include "node.h"
#include "build_ast.h"
#include "token.h"

void	ast_syntax_error(t_token *token)
{
	if (token->type == END)
		ft_dprintf(STDERR_FILENO, "%s 'new_line'\n", ERROR_MSG_BUILD_AST);
	else
		ft_dprintf(STDERR_FILENO, "%s '%s'\n", ERROR_MSG_BUILD_AST, token->str);
}

t_node	*build_ast(t_list *tokens)
{
	t_node	*current_node;
	t_node	*head;

	if (tokens == NULL)
		return (NULL);
	current_node = NULL;
	head = NULL;
	if (set_operator_type(tokens) == false)
		return (NULL);
	if (get_nodes(&current_node, &head, tokens) == false
		|| current_node == NULL)
	{
		ast_free(&head);
		return (NULL);
	}
	return (head);
}

bool	get_nodes(t_node **current_node, t_node **head, t_list *tokens)
{
	t_token			*first_token;
	t_token_type	token_type;

	if (current_node == NULL || head == NULL || tokens == NULL)
		return (false);
	first_token = (t_token *)tokens->content;
	token_type = first_token->type;
	if (token_type == END)
		return (true);
	if (token_type == OPERATOR_PIPE)
		return (add_pipe(current_node, head, tokens));
	if (token_type == OPERATOR_OR_IF || token_type == OPERATOR_AND_IF)
		return (add_connector(current_node, head, tokens, token_type));
	if (token_type == OPERATOR_SHELL_OPEN)
		return (add_subshell(current_node, head, tokens));
	return (add_command(current_node, head, tokens));
}
