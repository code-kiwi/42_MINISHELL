/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 08:55:13 by brappo            #+#    #+#             */
/*   Updated: 2024/04/17 14:33:54 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	remove_quote(char character, t_token_parser *parser)
{
	if (character == '"' && !parser->single_quoted)
	{
		parser->double_quoted = !parser->double_quoted;
		return (true);
	}
	if (character == '\'' && !parser->double_quoted)
	{
		parser->single_quoted = !parser->single_quoted;
		return (true);
	}
	return (false);
}

bool	search_wildcards(char *input, t_list **wildcards_pos)
{
	size_t			index;
	t_token_parser	parser;
	size_t			removed_quote;

	if (!input || !wildcards_pos || *wildcards_pos)
		return (false);
	t_token_parser_init(&parser);
	parser.end = &index;
	index = 0;
	removed_quote = 0;
	while (input[index] != '\0')
	{
		if (remove_quote(input[index], &parser))
			removed_quote += 1;
		else if (input[index] == '*' && !is_quoted(&parser))
		{
			if (!lst_push_front_content(wildcards_pos,
					input + index - removed_quote, NULL))
				return (ft_lstclear(wildcards_pos, NULL), false);
		}
		index++;
	}
	ft_lstreverse(wildcards_pos);
	return (true);
}
