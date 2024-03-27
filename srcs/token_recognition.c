/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:59:56 by brappo            #+#    #+#             */
/*   Updated: 2024/03/27 15:13:14by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	quote(t_token_parser *token_parser, char character)
{
	if (character == 26)
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

bool	is_token_end(t_token *token, char character, t_token_parser *token_parser)
{
	if (character == '\0')
		return (true);
	if (token->type == OPERATOR)
	{
		if (is_operator(character))
			return (false);
		return (true);
	} 
	if (quote(token_parser, character))
		return (false);
	if (!is_quoted(token_parser))
	{
		if (is_operator(character) && token->type == WORD)
			return (true);
		if (character == '\n')
			return (true);
		if (is_blank(character))
			return (true);
	}
	if (is_operator(character))
		token->type = OPERATOR;
	if (token->type == END)
		token->type = WORD;
	return (false);	
}

void	skip_blank(char *input, size_t *index)
{
	while (input[*index] != '\0')
	{
		if (!is_blank(input[*index]))
			break;
		*index += 1;
	}
}

t_token	*get_token(char *input, size_t *index)
{
	t_token_parser	token_parser;
	t_token			*token;
	size_t			start;

	start = *index;
	t_token_parser_init(&token_parser);
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

char	**token_recognition(char *input)
{
	size_t	index;
	t_token	*token;

	index = 0;
	if (input == NULL)
	{
		//ERROR
		return (NULL);
	}
	while (input[index] != '\0')
	{
		token = get_token(input, &index);
		printf("token str : %s\n", token->str);
		t_token_free(token);
		skip_blank(input, &index); 
	}
	return (NULL);
}