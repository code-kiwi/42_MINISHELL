/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:59:56 by brappo            #+#    #+#             */
/*   Updated: 2024/03/28 11:40:01 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		if (is_operator_character(character))
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

t_token	*get_token(char *input, size_t *index)
{
	t_token_parser	token_parser;
	t_token			*token;
	size_t			start;

	start = *index;
	t_token_parser_init(&token_parser, index, input);
	token = t_token_init();
	if (token == NULL)
		return (NULL);
	while (!is_token_end(token, input[*index], &token_parser))
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

t_list	*token_recognition(char *input)
{
	size_t	index;
	t_list	*tokens;

	index = 0;
	tokens = NULL;
	if (input == NULL)
		return (NULL);
	skip_blank(input, &index);
	while (input[index] != '\0')
	{
		ft_lstadd_front(&tokens, ft_lstnew(get_token(input, &index)));
		if (tokens == NULL || tokens->content == NULL)
		{
			ft_lstclear(&tokens, t_token_free);
			return (NULL);
		}
		skip_blank(input, &index);
	}
	ft_lstreverse(&tokens);
	return (tokens);
}
