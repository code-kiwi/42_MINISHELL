/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:23:01 by brappo            #+#    #+#             */
/*   Updated: 2024/05/10 16:56:00 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "minishell.h"
#include "token.h"
#include "build_ast.h"

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
		if (token->type == OPERATOR)
		{
			operator_index = array_find((void **)operators,
					string_equals, token->str);
			if (operator_index == -1)
			{
				ft_dprintf(STDERR_FILENO, "%s : '%s'\n",
					ERROR_MSG_BAD_OPERATOR, token->str);
				return (false);
			}
			token->type = (t_token_type)(operator_index + 3);
		}
		tokens = tokens->next;
	}
	return (true);
}
