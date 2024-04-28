/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:22:22 by brappo            #+#    #+#             */
/*   Updated: 2024/04/25 11:55:07 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

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

size_t	array_size(void **array)
{
	size_t	length;

	length = 0;
	if (array == NULL)
		return (0);
	while (array[length] != NULL)
		length++;
	return (length);
}
