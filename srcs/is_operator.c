/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:40:53 by brappo            #+#    #+#             */
/*   Updated: 2024/03/28 11:43:50 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_operator_character(char character)
{
	if (character == '>')
		return (true);
	if (character == '<')
		return (true);
	if (character == '&')
		return (true);
	if (character == '|')
		return (true);
	return (false);
}

void	get_operation(char **operations)
{
	operations[0] = ">>";
	operations[1] = "<<";
	operations[2] = ">";
	operations[3] = ">";
	operations[4] = "<";
	operations[5] = "||";
	operations[6] = "&&";
	operations[7] = NULL;
}

int	is_operator(t_token_parser *token_parser)
{
	char	temp;
	int		is_operator;
	char	*operations[OPERATOR_NUMBER];
	size_t	end;

	get_operation(operations);
	end = *(token_parser->end);
	temp = token_parser->input[end + 1];
	token_parser->input[end + 1] = '\0';
	is_operator = array_find((void **)operations,
			is_prefix, token_parser->input + token_parser->start);
	token_parser->input[end + 1] = temp;
	return (is_operator);
}
