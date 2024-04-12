/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:32:38 by brappo            #+#    #+#             */
/*   Updated: 2024/04/12 15:07:20 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*lst_push_front_content(t_list **head,
	void *content, void free_content(void *))
{
	t_list	*new_node;

	if (content == NULL)
		return (NULL);
	new_node = ft_lstnew(content);
	if (new_node == NULL)
	{
		if (free_content != NULL)
			free_content(content);
		return (NULL);
	}
	ft_lstadd_front(head, new_node);
	return (new_node);
}

void	**to_array(t_list *lst)
{
	size_t	length;
	void	**array;
	size_t	index;

	length = ft_lstsize(lst);
	if (length == 0)
		return (NULL);
	array = (void **)ft_calloc(length + 1, sizeof(char *));
	if (array == NULL)
		return (NULL);
	index = 0;
	while (index < length)
	{
		array[index] = lst->content;
		index++;
		lst = lst->next;
	}
	return (array);
}
