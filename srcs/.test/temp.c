/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:20:04 by brappo            #+#    #+#             */
/*   Updated: 2024/04/11 11:06:34 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_enum_str(char **array)
{
	array[0] = "END";
	array[1] = "WORD";
	array[2] = "OPERATOR";
	array[3] = "DGREAT";
	array[4] = "DLESS";
	array[5] = "GREAT";
	array[6] = "LESS";
	array[7] = "AND_IF";
	array[8] = "OR_IF";
	array[9] = "PIPE";
	array[10] = "SHELL_OPEN";
	array[11] = "SHELL_CLOSE";
}

void	print_token(void *token_void)
{
	t_token	*token;
	char	*enum_strs[12];

	if (token_void == NULL)
		return ;
	token = (t_token *)token_void;
	if (token->str != NULL)
		printf("%s : ", token->str);
	get_enum_str(enum_strs);
	printf("\033[0;35m");
	if (token->type > 11 || token->type < 0)
		printf("ERROR");
	printf("%s", enum_strs[token->type]);
	printf("\033[0m");
}
