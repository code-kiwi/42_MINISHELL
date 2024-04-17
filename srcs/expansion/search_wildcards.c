/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 08:55:13 by brappo            #+#    #+#             */
/*   Updated: 2024/04/17 09:29:03 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	search_wildcards(char *input, t_list **wildcards_pos)
{
	size_t			index;
	t_token_parser	parser;

	if (input == NULL || !wildcards_pos || *wildcards_pos)
		return (false);
	t_token_parser_init(&parser);
	parser.end = &index;
	index = 0;
	while (input[index] != '\0')
	{
		if (input[index] == '"' && !parser.single_quoted)
			parser.double_quoted = !parser.double_quoted;
		else if (input[index] == '\'' && !parser.double_quoted)
			parser.single_quoted = !parser.single_quoted;
		else if (input[index] == '*' && !is_quoted(&parser)
			&& !lst_push_front_content(wildcards_pos, *input + index, NULL))
		{
			ft_lstclear(wildcards_pos, NULL);
			return (false);
		}
		index++;
	}
	ft_lstreverse(wildcards_pos);
	return (true);
}
