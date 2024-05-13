/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:09:19 by brappo            #+#    #+#             */
/*   Updated: 2024/05/13 09:55:26 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "libft.h"
#include "token.h"

void	t_token_parser_init(t_token_parser *token_parser)
{
	token_parser->single_quoted = false;
	token_parser->double_quoted = false;
}

t_token	*t_token_init(char *str, t_token_type type)
{
	t_token	*token;

	if (type < 0 || type > 12)
		return (NULL);
	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->str = str;
	token->type = type;
	token->length = ft_strlen(str);
	return (token);
}

void	t_token_free(void *token_void)
{
	t_token	*token;

	if (token_void == NULL)
		return ;
	token = (t_token *)token_void;
	if (token->str != NULL)
		free(token->str);
	free(token);
}

/*
 *	Generates a list containing only one token with type END
 *	In case of ERROR, returns NULL
 */
t_list	*get_end_token_list(void)
{
	t_list	*end_token_link;
	t_token	*end_token;

	end_token = t_token_init(NULL, END);
	if (end_token == NULL)
		return (NULL);
	end_token_link = ft_lstnew((void *) end_token);
	if (end_token_link == NULL)
	{
		t_token_free(end_token);
		return (NULL);
	}
	return (end_token_link);
}
