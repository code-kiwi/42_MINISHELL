/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:12:32 by brappo            #+#    #+#             */
/*   Updated: 2024/04/12 16:34:52 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_quote(t_token_parser *parser, char *input)
{
	ft_memmove(input, input + 1, ft_strlen(input));
	*(parser->end) -= 1;
	if (*input == '\'')
		parser->single_quoted = !parser->single_quoted;
	else if (*input == '"')
		parser->double_quoted = !parser->double_quoted;
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

static bool	handle_wildcard(t_token_parser *parser, \
	t_list **wildcards_pos, char **input)
{
	size_t	index;

	index = *(parser->end);
	if ((*input)[index] == '*' && !is_quoted(parser))
	{
		if (!lst_push_front_content(wildcards_pos, *input + index, NULL))
		{
			ft_lstclear(wildcards_pos, NULL);
			return (false);
		}
	}
	return (true);
}

bool	quote_removal(char **input, t_minishell *shell, t_list **wildcards_pos)
{
	size_t			index;
	t_token_parser	parser;

	if (input == NULL || *input == NULL || wildcards_pos == NULL)
		return (false);
	t_token_parser_init(&parser);
	parser.end = &index;
	index = 0;
	*wildcards_pos = NULL;
	while ((*input)[index] != '\0')
	{
		if (((*input)[index] == '\'' && !parser.double_quoted)
			|| ((*input)[index] == '"' && !parser.single_quoted))
			remove_quote(&parser, *input + index);
		else if ((*input)[index] == '$' && !parser.single_quoted)
		{
			if (handle_variable(&parser, input, shell) == false)
				return (false);
		}
		else if (handle_wildcard(&parser, wildcards_pos, input) == false)
			return (false);
		index++;
	}
	ft_lstreverse(wildcards_pos);
	return (true);
}

t_list	*expand_string(char **input, t_minishell *shell)
{
	t_list	*wildcards_pos;
	t_list	*files;

	if (quote_removal(input, shell, &wildcards_pos) == false)
		return (NULL);
	if (wildcards_pos != NULL)
	{
		files = expand_wildcard(*input, wildcards_pos);
		ft_lstclear(&wildcards_pos, NULL);
		return (files);
	}
	files = ft_lstnew(*input);
	return (files);
}
