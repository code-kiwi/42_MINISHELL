/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:01:05 by brappo            #+#    #+#             */
/*   Updated: 2024/04/02 17:00:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h> 

bool	is_command_end(t_token_parser *token_parser, t_list *tokens)
{
	t_token	*last_token;

	if (is_quoted(token_parser) == true)
		return (false);
	last_token = (t_token *)ft_lstlast(tokens)->content;
	if (ft_strcmp(last_token->str, "||") == 0)
		return (false);
	return (true);
}

t_list	*token_recognition(char *input)
{
	t_token_parser	token_parser;
	t_list			*tokens;
	t_list			*last_token;
	char			*multi_ligne_input;

	t_token_parser_init(&token_parser);
	tokens = tokenize_str(input, &token_parser);
	if (tokens == NULL)
		return (NULL);
	while (is_command_end(&token_parser, tokens) == false)
	{
		multi_ligne_input = readline("> ");
		if (input == NULL)
		{
			ft_lstclear(&tokens, t_token_free);
			return (NULL);
		}
		last_token = ft_lstlast(tokens);
		last_token->next = tokenize_str(multi_ligne_input, &token_parser);
		free(multi_ligne_input);
		if (last_token->next == NULL)
		{
			ft_lstclear(&tokens, t_token_free);
			return (NULL);
		}
	}
	return (tokens);
}
