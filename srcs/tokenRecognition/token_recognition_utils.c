/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:09:19 by brappo            #+#    #+#             */
/*   Updated: 2024/04/11 10:55:17 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_token_parser_init(t_token_parser *token_parser)
{
	token_parser->single_quoted = false;
	token_parser->double_quoted = false;
}

t_token	*t_token_init(void)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
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

bool	is_blank(char character)
{
	if (character == '\t')
		return (true);
	if (character == ' ')
		return (true);
	return (false);
}

void	token_error(t_minishell *shell)
{
	handle_error(shell, TOKENIZATION_ERROR, EXIT_FAILURE);
}
