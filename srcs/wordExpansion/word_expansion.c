/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:03:37 by brappo            #+#    #+#             */
/*   Updated: 2024/04/05 11:23:51 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*envget(char *key)
{
	printf("key : %s\n", key);
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

ssize_t	expand_variable(char **input, size_t variable_start)
{
	ssize_t	key_coordinates[2];
	char	*value;
	ssize_t	result;

	get_variable_key_coordinates(*input, key_coordinates, variable_start);
	if (key_coordinates[0] == -1)
		return (-1);
	value = get_value_by_key_coordinates(*input, key_coordinates);
	if (value == NULL)
		return (-1);
	if (replace_key(input, key_coordinates, value, variable_start) == false)
	{
		free(value);
		return (-1);
	}
	printf("result : %s\n", *input);
	result = ft_strlen(value);
	free(value);
	return (result);
}

bool	expand_string(char **input)
{
	size_t	index;
	bool	single_quoted;
	bool	double_quoted;
	ssize_t	variable_length;

	single_quoted = false;
	double_quoted = false;
	if (input == NULL || *input == NULL)
		return (false);
	index = 0;
	while ((*input)[index] != '\0')
	{
		if ((*input)[index] == '\'' && !double_quoted)
			single_quoted = !single_quoted;
		else if ((*input)[index] == '\"' && !single_quoted)
			double_quoted = !double_quoted;
		if ((*input)[index] == '$' && !single_quoted)
		{
			variable_length = expand_variable(input, index);
			if (variable_length == -1)
				return (false);
			index += variable_length - 1;
		}
		index++;
	}
	return (true);
}
