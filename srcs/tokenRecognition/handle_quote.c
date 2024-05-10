/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:56:51 by brappo            #+#    #+#             */
/*   Updated: 2024/05/10 17:01:04 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "token.h"

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
