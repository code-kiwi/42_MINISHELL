/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:03:37 by brappo            #+#    #+#             */
/*   Updated: 2024/04/05 16:05:32 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*envget(char *key)
{
	if (*key == '?')
		return (ft_strdup("0"));
	return (ft_strdup("machin"));
}

bool	replace_key(char **input, ssize_t *key_coordinates, char *value,
	size_t variable_start)
{
	char	*result;
	size_t	result_length;

	result_length = variable_start + ft_strlen(value);
	result_length += ft_strlen((*input) + key_coordinates[1]) + 1;
	result = (char *)ft_calloc(result_length, sizeof(char));
	if (result == NULL)
		return (false);
	ft_memcpy(result, *input, variable_start);
	ft_strlcat(result, value, result_length);
	if ((*input)[variable_start + 1] == '{')
		ft_strlcat(result, *input + key_coordinates[1] + 1, result_length);
	else
		ft_strlcat(result, *input + key_coordinates[1], result_length);
	free(*input);
	*input = result;
	return (true);
}

char	*get_value_by_key_coordinates(char *input, ssize_t *key_coordinates)
{
	char	temp;
	char	*value;

	temp = input[key_coordinates[1]];
	input[key_coordinates[1]] = '\0';
	value = envget(input + key_coordinates[0]);
	input[key_coordinates[1]] = temp;
	return (value);
}

ssize_t	handle_invalid_variable(char *input, ssize_t *key_coordinates,
	size_t variable_start, bool double_quoted)
{
	char	second_character;
	char	*variable;

	second_character = input[key_coordinates[0]];
	if (!double_quoted && (second_character == '\''
			|| second_character == '"'))
	{
		variable = input + variable_start;
		ft_memmove(variable, variable + 1, ft_strlen(variable));
		return (0);
	}
	return (1);
}

ssize_t	expand_variable(char **input, size_t variable_start, bool double_quoted)
{
	ssize_t	key_coordinates[2];
	char	*value;
	ssize_t	result;

	get_variable_key_coordinates(*input, key_coordinates, variable_start);
	if (key_coordinates[0] == -1)
		return (-1);
	if ((size_t)key_coordinates[1] == variable_start + 1)
		return (handle_invalid_variable(*input, key_coordinates,
				variable_start, double_quoted));
	value = get_value_by_key_coordinates(*input, key_coordinates);
	if (value == NULL)
		return (-1);
	if (replace_key(input, key_coordinates, value, variable_start) == false)
	{
		free(value);
		return (-1);
	}
	result = ft_strlen(value);
	free(value);
	return (result);
}
