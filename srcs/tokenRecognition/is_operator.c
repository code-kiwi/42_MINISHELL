/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:40:53 by brappo            #+#    #+#             */
/*   Updated: 2024/04/25 11:51:27 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

void	get_operation(char **operations)
{
	operations[0] = DGREAT;
	operations[1] = DLESS;
	operations[2] = GREAT;
	operations[3] = LESS;
	operations[4] = AND_IF;
	operations[5] = OR_IF;
	operations[6] = PIPE;
	operations[7] = SHELL_OPEN;
	operations[8] = SHELL_CLOSE;
	operations[9] = NULL;
}

int	is_operator(t_token_parser *token_parser)
{
	char	temp;
	int		is_operator;
	char	*operations[OPERATOR_NUMBER + 1];
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
