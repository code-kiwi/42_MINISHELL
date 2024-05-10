/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:35:42 by brappo            #+#    #+#             */
/*   Updated: 2024/05/10 16:56:04 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "libft.h"
#include "token.h"

bool	is_redirection(t_token_type token_type)
{
	return (token_type == OPERATOR_DGREAT
		|| token_type == OPERATOR_DLESS
		|| token_type == OPERATOR_GREAT
		|| token_type == OPERATOR_LESS);
}

bool	is_cmd_token(t_list *tokens)
{
	t_token	*token;

	if (tokens == NULL || tokens->content == NULL)
		return (false);
	token = (t_token *)tokens->content;
	return (token->type == WORD || is_redirection(token->type));
}

static size_t	count_argv(t_list *tokens)
{
	t_token	*token;
	size_t	argv_count;

	argv_count = 0;
	while (is_cmd_token(tokens))
	{
		token = tokens->content;
		if (is_redirection(token->type))
			tokens = tokens->next;
		else
			argv_count++;
		if (tokens != NULL)
			tokens = tokens->next;
	}
	return (argv_count);
}

char	**get_argv(t_list *tokens)
{
	t_token	*token;
	char	**argv;
	size_t	index;

	if (tokens == NULL)
		return (NULL);
	argv = ft_calloc(count_argv(tokens) + 1, sizeof(char *));
	if (argv == NULL)
		return (NULL);
	index = 0;
	while (is_cmd_token(tokens))
	{
		token = (t_token *)tokens->content;
		if (is_redirection(token->type))
			tokens = tokens->next;
		else
		{
			argv[index] = token->str;
			index++;
		}
		if (tokens != NULL)
			tokens = tokens->next;
	}
	return (argv);
}
