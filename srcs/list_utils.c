/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:32:38 by brappo            #+#    #+#             */
/*   Updated: 2024/03/28 09:46:15 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_list *lst)
{
	t_token	*token;

	if (lst == NULL)
	{
		printf("NULL");
		return ;
	}
	while (lst != NULL)
	{
		token = lst->content;
		printf("%s\n", token->str);
		lst = lst->next; 
	}	
}