/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:32:38 by brappo            #+#    #+#             */
/*   Updated: 2024/04/03 10:04:00 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
