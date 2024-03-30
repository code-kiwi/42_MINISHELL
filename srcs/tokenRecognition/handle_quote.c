/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:56:51 by brappo            #+#    #+#             */
/*   Updated: 2024/03/28 09:58:04 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_quoted(t_token_parser *token_parser)
{
	return (token_parser->single_quoted || token_parser->double_quoted);
}

bool	handle_quote(t_token_parser *token_parser, char character)
{
	if (character == '\'')
	{
		if (token_parser->single_quoted == true)
			token_parser->single_quoted = false;
		else if (token_parser->double_quoted == false)
			token_parser->single_quoted = true;
		return (true);
	}
	if (character == '"')
	{
		if (token_parser->double_quoted == true)
			token_parser->double_quoted = false;
		else if (token_parser->single_quoted == false)
			token_parser->double_quoted = true;
		return (true);
	}
	return (false);
}
