/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:12:32 by brappo            #+#    #+#             */
/*   Updated: 2024/04/25 11:41:49 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "token.h"
#include "expansion.h"

static void	remove_quote(t_token_parser *parser, char *input, char options)
{
	if (*input == '\'')
		parser->single_quoted = !parser->single_quoted;
	else if (*input == '"')
		parser->double_quoted = !parser->double_quoted;
	if (options & 1)
	{
		ft_memmove(input, input + 1, ft_strlen(input));
		*(parser->end) -= 1;
	}
}

static bool	handle_variable(t_token_parser *parser, \
	char **input, t_minishell *shell, char options)
{
	size_t	*index;
	ssize_t	var_length;

	if (!((options >> 1) & 1))
		return (true);
	index = parser->end;
	if ((*input)[*index] != '$' || parser->single_quoted)
		return (true);
	var_length = expand_variable(input, *index, \
		parser->double_quoted, shell);
	if (var_length < 0)
		return (false);
	*index += var_length - 1;
	return (true);
}

static bool	handle_wildcards(t_list **wildcards_pos, t_token_parser *parser, \
	char *input, char options)
{
	size_t	index;

	index = *(parser->end);
	if (!((options >> 2) & 1))
		return (true);
	if (input[index] == '*' && !is_quoted(parser))
	{
		if (!lst_push_front_content(wildcards_pos,
				input + index, NULL))
		{
			ft_lstclear(wildcards_pos, NULL);
			return (false);
		}
	}
	return (true);
}

static t_list	*get_arguments(char *str, t_list *wildcards)
{
	char	*str_dup;
	t_list	*arguments;

	if (wildcards == NULL)
	{
		str_dup = ft_strdup(str);
		if (str_dup == NULL)
			return (NULL);
		arguments = ft_lstnew(str_dup);
		if (arguments == NULL)
			free(str_dup);
		return (arguments);
	}
	else
	{
		ft_lstreverse(&wildcards);
		arguments = expand_wildcard(str, wildcards);
		ft_lstclear(&wildcards, NULL);
		return (arguments);
	}
}

t_list	*expand_string(char **str, t_minishell *shell, char options)
{
	size_t			index;
	t_token_parser	parser;
	t_list			*wildcard_pos;

	if (str == NULL || *str == NULL || shell == NULL)
		return (NULL);
	t_token_parser_init(&parser);
	parser.end = &index;
	index = 0;
	wildcard_pos = NULL;
	while ((*str)[index] != '\0')
	{
		if (((*str)[index] == '\'' && !parser.double_quoted)
			|| ((*str)[index] == '"' && !parser.single_quoted))
			remove_quote(&parser, *str + index, options);
		else if (!handle_wildcards(&wildcard_pos, &parser, *str, options))
			return (NULL);
		else if ((*str)[index] == '$' \
			&& !handle_variable(&parser, str, shell, options))
			return (NULL);
		index++;
	}
	return (get_arguments(*str, wildcard_pos));
}
