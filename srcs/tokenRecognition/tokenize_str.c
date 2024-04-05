/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:59:56 by brappo            #+#    #+#             */
/*   Updated: 2024/04/05 09:08:00 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_token_end(t_token *token, char character, \
		t_token_parser *token_parser)
{
	if (character == '\0')
		return (true);
	if (token->type == OPERATOR)
	{
		if (is_operator(token_parser) != -1)
			return (false);
		return (true);
	}
	if (handle_quote(token_parser, character))
		return (false);
	if (!is_quoted(token_parser))
	{
		if (ft_strchr(OPERATOR_CHARACTER, character) != NULL)
		{
			if (token->type == WORD)
				return (true);
			token->type = OPERATOR;
		}
		if (character == '\n' || is_blank(character))
			return (true);
	}
	if (token->type == END)
		token->type = WORD;
	return (false);
}

void	skip_blank(char *input, size_t *index)
{
	while (input[*index] != '\0')
	{
		if (!is_blank(input[*index]))
			break ;
		*index += 1;
	}
}

t_token	*get_token(char *input, size_t *index, t_token_parser *token_parser)
{
	t_token			*token;
	size_t			start;

	start = *index;
	token_parser->start = *index;
	token = t_token_init();
	if (token == NULL)
		return (NULL);
	while (!is_token_end(token, input[*index], token_parser))
		*index += 1;
	token->length = *index - start;
	token->str = ft_substr(input, start, token->length);
	if (token->str == NULL)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

t_list	*tokenize_str(char *str, t_token_parser *token_parser)
{
	size_t	index;
	t_list	*tokens;

	index = 0;
	tokens = NULL;
	token_parser->end = &index;
	token_parser->input = str;
	if (str == NULL)
		return (NULL);
	skip_blank(str, &index);
	while (str[index] != '\0')
	{
		lst_push_front_content(&tokens, get_token(str, &index, token_parser));
		if (tokens == NULL || tokens->content == NULL)
		{
			ft_lstclear(&tokens, t_token_free);
			return (NULL);
		}
		skip_blank(str, &index);
	}
	ft_lstreverse(&tokens);
	return (tokens);
}
