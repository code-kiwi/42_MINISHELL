/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:26:15 by brappo            #+#    #+#             */
/*   Updated: 2024/04/10 14:09:17 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	size_t	length;
	size_t	index;
	char	*a_str;
	char	*b_str;

	if (a == NULL || b == NULL)
		return (a == b);
	a_str = (char *)a;
	b_str = (char *)b;
	length = ft_strlen(a_str);
	index = 0;
	while (index <= length)
	{
		if (a_str[index] != b_str[index])
			return (false);
		index++;
	}
	return (true);
}
