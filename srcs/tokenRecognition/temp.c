/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:20:04 by brappo            #+#    #+#             */
/*   Updated: 2024/04/11 09:32:32 by brappo           ###   ########.fr       */
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
	switch (token->type)
	{
		case END :
			printf("END");
			break ;
		case WORD :
			printf("WORD");
			break ;
		case OPERATOR :
			printf("OPERATOR");
			break ;
		case OPERATOR_DGREAT :
			printf("OPERATOR_DGREAT");
			break ;
		case OPERATOR_DLESS :
			printf("OPERATOR_DLESS");
			break ;
		case OPERATOR_GREAT :
			printf("OPERATOR_GREAT");
			break ;
		case OPERATOR_LESS :
			printf("OPERATOR_LESS");
			break ;
		case OPERATOR_AND_IF :
			printf("OPERATOR_AND_IF");
			break ;
		case OPERATOR_OR_IF :
			printf("OPERATOR_OR_IF");
			break ;
		case OPERATOR_PIPE :
			printf("OPERATOR_PIPE");
			break ;
		case OPERATOR_SHELL_OPEN :
			printf("OPERATOR_SHELL_OPEN");
			break ;
		case OPERATOR_SHELL_CLOSE :
			printf("OPERATOR_SHELL_CLOSE");
			break;
		default :
			printf("ERROR");
	}
	printf("\033[0m");
}
