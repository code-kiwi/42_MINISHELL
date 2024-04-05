/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:20:04 by brappo            #+#    #+#             */
/*   Updated: 2024/04/05 09:07:30 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(void *token_void)
{
	t_token	*token;

	if (token_void == NULL)
		return ;
	token = (t_token *)token_void;
	if (token->str != NULL)
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
