/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:01:05 by brappo            #+#    #+#             */
/*   Updated: 2024/04/03 09:58:30 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h> 

void	add_end_token(t_list **tokens)
{
	t_token	*end_token;
	t_list	*new_node;

	end_token = t_token_init();
	if (end_token == NULL)
	{
		ft_lstclear(tokens, t_token_free);
		*tokens = NULL;
		return ;
	}
	new_node = ft_lstnew((void *)end_token);
	if (new_node == NULL)
	{
		t_token_free(end_token);
		ft_lstclear(tokens, t_token_free);
		*tokens = NULL;
		return ;
	}
	ft_lstadd_back(tokens, new_node);
}

bool	is_command_end(t_token_parser *token_parser, t_list *tokens)
{
	t_token	*last_token;

	if (tokens == NULL)
		return (true);
	if (is_quoted(token_parser) == true)
		return (false);
	last_token = (t_token *)ft_lstlast(tokens)->content;
	if (ft_strcmp(last_token->str, AND_IF) == 0)
		return (false);
	if (ft_strcmp(last_token->str, OR_IF) == 0)
		return (false);
	if (ft_strcmp(last_token->str, PIPE) == 0)
		return (false);
	return (true);
}

t_list	*tokenize_input(char *prompt, t_token_parser *token_parser)
{
	char	*input;
	t_list	*tokens;

	input = readline(prompt);
	if (input == NULL)
		return (NULL);
	tokens = tokenize_str(input, token_parser);
	free(input);
	if (tokens == NULL)
		return (NULL);
	return (tokens);
}

t_list	*token_recognition(char *input)
{
	t_token_parser	token_parser;
	t_list			*tokens;
	bool			is_end_quoted;
	t_list			*second_tokens;

	t_token_parser_init(&token_parser);
	tokens = tokenize_str(input, &token_parser);
	if (tokens == NULL && *input)
		return (NULL);
	while (is_command_end(&token_parser, tokens) == false)
	{
		is_end_quoted = is_quoted(&token_parser);
		second_tokens = tokenize_input("> ", &token_parser);
		if (!append_token_list(is_end_quoted, tokens, second_tokens))
		{
			ft_lstclear(&tokens, t_token_free);
			ft_lstclear(&second_tokens, t_token_free);
			return (NULL);
		}
	}
	add_end_token(&tokens);
	return (tokens);
}
