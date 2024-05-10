/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable_key.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 08:34:50 by brappo            #+#    #+#             */
/*   Updated: 2024/05/10 16:59:03 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "libft.h"

static bool	is_char_name(char c)
{
	if (ft_isalnum(c))
		return (true);
	if (c == '_')
		return (true);
	return (false);
}

static ssize_t	find_bracket(char *input, ssize_t variable_start)
{
	char	*closing_bracket;

	closing_bracket = ft_strchr(input + variable_start, '}');
	if (closing_bracket == NULL)
		return (-1);
	return (closing_bracket - input);
}

static bool	is_string_name(char *input, ssize_t start, ssize_t end)
{
	ssize_t	index;

	index = start;
	if (input == NULL || start < 0)
		return (false);
	while (input[index] && index < end)
	{
		if (!is_char_name(input[index]))
			return (false);
		index++;
	}
	return (true);
}

static ssize_t	end_of_name(char *input, ssize_t variable_start)
{
	ssize_t	index;

	index = variable_start;
	while (input[index] != '\0')
	{
		if (index == variable_start && input[index] == '?')
			return (index + 1);
		if (!is_char_name(input[index]))
			break ;
		index++;
	}
	return (index);
}

void	get_variable_key_coordinates(char *input, ssize_t *coordinates,
	size_t variable_start)
{
	ssize_t	key_end;
	ssize_t	key_start;

	coordinates[0] = -1;
	if (input == NULL || variable_start >= ft_strlen(input)
		|| input[variable_start] != '$')
		return ;
	key_start = variable_start + 1;
	if (input[key_start] == '{')
	{
		key_start++;
		key_end = find_bracket(input, key_start);
		if (key_end == -1 || !is_string_name(input, key_start, key_end))
			return ;
	}
	else
		key_end = end_of_name(input, key_start);
	coordinates[0] = key_start;
	coordinates[1] = key_end;
}
