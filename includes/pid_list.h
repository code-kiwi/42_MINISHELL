/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:50:52 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/25 10:54:22 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PID_LIST_H
# define PID_LIST_H

# include <stdlib.h>

typedef struct s_pid_list
{
	pid_t				pid;
	struct s_pid_list	*next;
}	t_pid_list;

// t_pid_list functions
t_pid_list	*pid_list_new(pid_t pid);
void		pid_list_add_back(t_pid_list **list, t_pid_list *new_elt);
void		pid_list_clear(t_pid_list **list);
size_t		pid_list_size(t_pid_list *list);

#endif
