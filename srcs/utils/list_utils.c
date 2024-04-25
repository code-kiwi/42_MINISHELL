/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:32:38 by brappo            #+#    #+#             */
/*   Updated: 2024/04/25 12:03:46 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

t_list	*lst_extract_min(t_list **head, int (*cmp)(void *, void *))
{
	t_list	*min;
	t_list	*min_prev;
	t_list	*current;

	current = *head;
	min = current;
	min_prev = NULL;
	if (current == NULL)
		return (NULL);
	while (current->next != NULL)
	{
		if (cmp(min->content, current->next->content) > 0)
		{
			min = current->next;
			min_prev = current;
		}
		current = current->next;
	}
	if (min_prev == NULL)
		*head = min->next;
	else
		min_prev->next = min->next;
	min->next = NULL;
	return (min);
}

t_list	*lst_sort(t_list **to_sort, int (*cmp)(void *, void *))
{
	t_list	*sorted_list;
	t_list	*min;

	sorted_list = NULL;
	if (to_sort == NULL || *to_sort == NULL)
		return (NULL);
	while (*to_sort != NULL)
	{
		min = lst_extract_min(to_sort, cmp);
		ft_lstadd_front(&sorted_list, min);
	}
	ft_lstreverse(&sorted_list);
	*to_sort = sorted_list;
	return (sorted_list);
}
