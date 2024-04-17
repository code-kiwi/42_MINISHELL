/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:12:32 by brappo            #+#    #+#             */
/*   Updated: 2024/04/17 11:35:07 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_quote(t_token_parser *parser, char *input)
{
	if (*input == '\'')
		parser->single_quoted = !parser->single_quoted;
	else if (*input == '"')
		parser->double_quoted = !parser->double_quoted;
	ft_memmove(input, input + 1, ft_strlen(input));
	*(parser->end) -= 1;
}

static bool	handle_variable(t_token_parser *parser, \
	char **input, t_minishell *shell)
{
	size_t	index;
	ssize_t	var_length;

	index = *(parser->end);
	var_length = expand_variable(input, index, \
		parser->double_quoted, shell);
	if (var_length < 0)
		return (false);
	index += var_length;
	return (true);
}

bool	quote_removal(char **input, t_minishell *shell)
{
	size_t			index;
	t_token_parser	parser;

	if (input == NULL || *input == NULL)
		return (false);
	t_token_parser_init(&parser);
	parser.end = &index;
	index = 0;
	while ((*input)[index] != '\0')
	{
		if (((*input)[index] == '\'' && !parser.double_quoted)
			|| ((*input)[index] == '"' && !parser.single_quoted))
			remove_quote(&parser, *input + index);
		else if ((*input)[index] == '$' && !parser.single_quoted
			&& !handle_variable(&parser, input, shell))
			return (false);
		index++;
	}
	return (true);
}

t_list	*expand_string(t_token *token, t_minishell *shell)
{
	t_list	*wildcards_pos;
	t_list	*files;

	wildcards_pos = NULL;
	if (token->type != ASSIGNEMENT_WORD
		&& !search_wildcards(token->str, &wildcards_pos))
		return (NULL);
	if (!quote_removal(&token->str, shell))
	{
		ft_lstclear(&wildcards_pos, NULL);
		return (NULL);
	}
	if (wildcards_pos != NULL)
	{
		files = expand_wildcard(token->str, wildcards_pos);
		ft_lstclear(&wildcards_pos, NULL);
		return (files);
	}
	files = NULL;
	if (!add_token(&files, token->str, token->type))
		return (NULL);
	return (files);
}
