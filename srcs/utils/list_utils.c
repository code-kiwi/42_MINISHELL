/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:32:38 by brappo            #+#    #+#             */
/*   Updated: 2024/03/29 11:31:36 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_type(t_token_type token_type)
{
	printf("\033[0;35m");
	if (token_type == END)
		printf("END");
	else if (token_type == WORD)
		printf("WORD");
	else if (token_type == OPERATOR)
		printf("OPERATOR");
	printf("\033[0m");
}

void	print_list_token(t_list *lst)
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
		printf("%s : ", token->str);
		print_token_type(token->type);
		printf("\n");
		lst = lst->next;
	}
}

t_list	*lst_push_front_content(t_list **head, void *content)
{
	t_list	*new_node;

	if (content == NULL)
		return (NULL);
	new_node = ft_lstnew(content);
	if (new_node == NULL)
	{
		free(content);
		return (NULL);
	}
	ft_lstadd_front(head, new_node);
	return (new_node);
}
