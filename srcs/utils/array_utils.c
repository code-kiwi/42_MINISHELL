/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:22:22 by brappo            #+#    #+#             */
/*   Updated: 2024/04/04 09:53:04 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	array_find(void **array, bool (equal)(void *a, void *b), void *value)
{
	size_t	index;

	index = 0;
	if (array == NULL)
		return (-1);
	while (array[index] != NULL)
	{
		if (equal(array[index], value) == true)
			return (index);
		index++;
	}
	return (-1);
}

int	array_if(void **array, bool condition(void *elem), size_t size)
{
	size_t	index;

	index = 0;
	if (array == NULL)
		return (-1);
	while (index < size)
	{
		if (condition(array[index]) == true)
			return (index);
		index++;
	}
	return (index);
}
