/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:22:22 by brappo            #+#    #+#             */
/*   Updated: 2024/04/29 16:08:25 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"

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

bool	array_copy(void ***dest, void ***src, size_t dest_length)
{
	size_t	index;

	if (dest == NULL || src == NULL || dest_length == 0)
		return (false);
	index = 0;
	dest[dest_length - 1] = NULL;
	while (index < dest_length - 1 && src[index])
	{
		dest[index] = src[index];
		index++;
	}
	return (index == dest_length - 1);
}

char	**dup_str_array(char **array)
{
	char	**result;
	size_t	array_length;
	size_t	index;

	if (array == NULL)
		return (NULL);
	array_length = array_size((void **)array);
	result = ft_calloc(array_length + 1, sizeof(char *));
	if (result == NULL)
		return (NULL);
	index = 0;
	while (index < array_length)
	{
		result[index] = ft_strdup(array[index]);
		if (result[index] == NULL)
		{
			ft_free_str_array(&array);
			return (NULL);
		}
		index++;
	}
	return (result);
}
