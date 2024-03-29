/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:09:19 by brappo            #+#    #+#             */
/*   Updated: 2024/03/28 11:06:30 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_token_parser_init(t_token_parser *token_parser,
		size_t *index, char *input)
{
	token_parser->single_quoted = false;
	token_parser->double_quoted = false;
	token_parser->end = index;
	token_parser->start = *index;
	token_parser->input = input;
}

t_token	*t_token_init(void)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		return (NULL);
	return (token);
}

void	t_token_free(void	*token_void)
{
	t_token	*token;

	token = (t_token *)token_void;
	free(token->str);
	free(token);
}

bool	is_blank(char character)
{
	if (character == '\t')
		return (true);
	if (character == ' ')
		return (true);
	return (false);
}
