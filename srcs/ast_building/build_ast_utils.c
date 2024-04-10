/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:23:01 by brappo            #+#    #+#             */
/*   Updated: 2024/04/10 10:36:40 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	set_operator_type(t_list *tokens)
{
	int		operator_index;
	t_token	*token;
	char	*operators[OPERATOR_NUMBER + 1];

	if (tokens == NULL)
		return (false);
	get_operation(operators);
	while (tokens->next != NULL)
	{
		token = (t_token *)tokens->content;
		if (token->type != OPERATOR)
			continue ;
		operator_index = array_find(operators, string_equals, token->str);
		if (operator_index == -1)
			return (false);
		token->type = (t_token_type)operator_index;
		tokens = tokens->next;
	}
	return (true);
}