/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:01:05 by brappo            #+#    #+#             */
/*   Updated: 2024/04/05 09:22:42 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

bool	add_end_token(t_list **tokens)
{
	t_token	*end_token;
	t_list	*new_node;

	end_token = t_token_init();
	if (end_token == NULL)
		return (false);
	new_node = ft_lstnew((void *)end_token);
	if (new_node == NULL)
	{
		t_token_free(end_token);
		return (false);
	}
	ft_lstadd_back(tokens, new_node);
	return (true);
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

void	merge_inputs(t_minishell *shell, char *input, bool is_end_quoted)
{
	char	*separator;

	if (input == NULL)
		token_error(shell);
	if (is_end_quoted)
		separator = "\n";
	else
		separator = " ";
	if (bridge_into_first(&shell->input, input, separator) == false)
	{
		free(input);
		token_error(shell);
	}
}

t_list	*tokenize_input(t_minishell *shell, char *prompt,
	t_token_parser *token_parser, bool is_end_quoted)
{
	char	*input;
	t_list	*tokens;

	input = readline(prompt);
	merge_inputs(shell, input, is_end_quoted);
	tokens = tokenize_str(input, token_parser);
	if (tokens == NULL && *input)
	{
		free(input);
		handle_error(shell, TOKENIZATION_ERROR, EXIT_FAILURE);
	}
	free(input);
	return (tokens);
}

void	token_recognition(t_minishell *shell)
{
	t_token_parser	token_parser;
	bool			is_end_quoted;
	t_list			*second_tokens;

	t_token_parser_init(&token_parser);
	shell->tokens = tokenize_str(shell->input, &token_parser);
	if (shell->tokens == NULL && (shell->input == NULL || *shell->input))
		token_error(shell);
	while (is_command_end(&token_parser, shell->tokens) == false)
	{
		is_end_quoted = is_quoted(&token_parser);
		second_tokens = tokenize_input(shell, MULTIPLE_LINE_PROMPT,
				&token_parser, is_end_quoted);
		if (!append_token_list(is_end_quoted, shell->tokens, second_tokens))
		{
			ft_lstclear(&second_tokens, t_token_free);
			token_error(shell);
		}
	}
	if (add_end_token(&shell->tokens) == false)
		token_error(shell);
}
