/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:01:05 by brappo            #+#    #+#             */
/*   Updated: 2024/04/02 13:43:01 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h> 

bool	is_command_end(t_token_parser *token_parser)
{
	int		operator;

	operator = is_operator(token_parser);
	if (is_quoted(token_parser) == true)
		return (false);
	if (operator >= 4)
		return (false);
	return (true);
}

t_list	*token_recognition(char *input)
{
	t_token_parser	token_parser;
	t_list			*tokens;
	t_list			*last_token;

	t_token_parser_init(&token_parser);
	tokens = tokenize_str(input, &token_parser);
	if (tokens == NULL)
		return (NULL);
	while (is_command_end(&token_parser) == false)
	{
		free(input);
		input = readline("> ");
		if (input == NULL)
		{
			ft_lstclear(&tokens, t_token_free);
			return (NULL);
		}
		last_token = ft_lstlast(tokens);
		last_token->next = tokenize_str(input, &token_parser);
		if (last_token->next == NULL)
		{
			ft_lstclear(&tokens, t_token_free);
			return (NULL);
		}
	}
	return (tokens);
}
