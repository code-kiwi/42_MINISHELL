/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pid_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:54:49 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/10 15:13:43 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Allocates a t_pid_list element and returns a pointer to it
 *	The pid value is set to the given pid
 *	In case of ERROR, returns NULL
 */
t_pid_list	*pid_list_new(pid_t pid)
{
	t_pid_list	*new;

	new = (t_pid_list *) ft_calloc(1, sizeof(t_pid_list));
	if (new == NULL)
		return (NULL);
	new->pid = pid;
	return (new);
}

/*
 *	Adds the new element at the end of the given pid_list
 *	If the list did not exist (*list is NULL) then the *list is set to new
 */
void	pid_list_add_back(t_pid_list **list, t_pid_list *new)
{
	t_pid_list	*current;

	if (list == NULL || new == NULL)
		return ;
	if (*list == NULL)
		*list = new;
	else
	{
		current = *list;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

/*
 *	Frees the memory allocated for the given t_pid_list
 *	Set the *list pointer to NULL
 */
void	pid_list_clear(t_pid_list **list)
{
	t_pid_list	*current;
	t_pid_list	*next;

	if (list == NULL || *list == NULL)
		return ;
	current = *list;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*list = NULL;
}
