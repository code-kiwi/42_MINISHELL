/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:09:19 by brappo            #+#    #+#             */
/*   Updated: 2024/04/03 10:03:49 by brappo           ###   ########.fr       */
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

void	print_token(void *token_void)
{
	t_token	*token;

	if (token_void == NULL)
		return ;
	token = (t_token *)token_void;
	printf("%s : ", token->str);
	printf("\033[0;35m");
	if (token->type == END)
		printf("END");
	else if (token->type == WORD)
		printf("WORD");
	else if (token->type == OPERATOR)
		printf("OPERATOR");
	printf("\033[0m");
	printf("\n");
}
