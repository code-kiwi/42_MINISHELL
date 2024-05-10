/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:26:15 by brappo            #+#    #+#             */
/*   Updated: 2024/05/10 17:02:21 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "libft.h"

bool	is_prefix(void	*word, void *prefix)
{
	char	*word_str;
	char	*prefix_str;

	word_str = (char *)word;
	prefix_str = (char *)prefix;
	return (ft_strstr(word_str, prefix_str) == word);
}

char	*join_into_dest(char **dest, char *str)
{
	char	*temp;

	temp = ft_strjoin(*dest, str);
	if (temp == NULL)
		return (NULL);
	free(*dest);
	*dest = temp;
	return (temp);
}

char	*bridge(char *first, char *second, char *separator)
{
	char	*result;
	size_t	first_length;
	size_t	result_length;

	first_length = ft_strlen(first);
	result_length = first_length + ft_strlen(second) + ft_strlen(separator) + 1;
	if (result_length == 0)
		return (NULL);
	result = (char *)ft_calloc(result_length, sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, first, first_length);
	ft_strlcat(result, separator, result_length);
	ft_strlcat(result, second, result_length);
	return (result);
}

char	*bridge_into_first(char **first, char *second, char *separator)
{
	char	*temp;

	temp = bridge(*first, second, separator);
	if (temp == NULL)
		return (NULL);
	free(*first);
	*first = temp;
	return (temp);
}

bool	string_equals(void *a, void *b)
{
	return (ft_strcmp((char *)a, (char *)b) == 0);
}
