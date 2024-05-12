/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:01:05 by brappo            #+#    #+#             */
/*   Updated: 2024/05/12 10:52:24 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "libft.h"
#include "minishell.h"
#include "token.h"
#include <readline/readline.h>
#include "signals.h"
#include <errno.h>

static bool	add_end_token(t_list **tokens)
{
	t_list	*last_element;
	t_list	**head;

	if (tokens == NULL)
		return (false);
	last_element = ft_lstlast(*tokens);
	if (last_element == NULL)
		head = tokens;
	else
		head = &last_element->next;
	if (lst_push_front_content(head,
			t_token_init(NULL, END), t_token_free))
	{
		return (true);
	}
	return (false);
}

static bool	is_command_end(t_token_parser *token_parser, t_list *tokens)
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

static void	merge_inputs(t_minishell *shell, char *input, bool is_end_quoted)
{
	char	*separator;

	if (input == NULL)
		handle_error(shell, ERROR_MSG_TOKENIZATION, EXIT_FAILURE);
	if (is_end_quoted)
		separator = "\n";
	else
		separator = " ";
	if (bridge_into_first(&shell->input, input, separator) == false)
	{
		free(input);
		handle_error(shell, ERROR_MSG_TOKENIZATION, EXIT_FAILURE);
	}
}

static t_list	*tokenize_input(t_minishell *shell,
	t_token_parser *token_parser, bool is_end_quoted)
{
	char	*input;
	t_list	*tokens;

	if (shell->is_a_tty)
		input = readline(MULTIPLE_LINE_PROMPT);
	else
		input = get_next_line_no_linebreak(STDIN_FILENO);
	if (get_sigint())
	{
		if (errno == EINTR)
			errno = 0;
		free(input);
		return (NULL);
	}
	if (interrupted(input))
		handle_error(shell, SHELL_EOF, EXIT_FAILURE);
	merge_inputs(shell, input, is_end_quoted);
	tokens = tokenize_str(input, token_parser);
	if (tokens == NULL && *input)
	{
		free(input);
		handle_error(shell, ERROR_MSG_TOKENIZATION, EXIT_FAILURE);
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
	if (shell->tokens == NULL && (shell->input == NULL || *(shell->input)))
		handle_error(shell, ERROR_MSG_TOKENIZATION, EXIT_FAILURE);
	while (is_command_end(&token_parser, shell->tokens) == false)
	{
		is_end_quoted = is_quoted(&token_parser);
		second_tokens = tokenize_input(shell, &token_parser, is_end_quoted);
		if (catch_sigint())
			return (ft_lstclear(&shell->tokens, t_token_free));
		if (!append_token_list(is_end_quoted, &shell->tokens, second_tokens))
		{
			ft_lstclear(&second_tokens, t_token_free);
			handle_error(shell, ERROR_MSG_TOKENIZATION, EXIT_FAILURE);
		}
	}
	if (add_end_token(&shell->tokens) == false)
		handle_error(shell, ERROR_MSG_TOKENIZATION, EXIT_FAILURE);
}
