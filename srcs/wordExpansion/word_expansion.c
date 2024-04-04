/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:03:37 by brappo            #+#    #+#             */
/*   Updated: 2024/04/04 14:35:49 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*envget(char *key)
{
	printf("key : %s\n", key);
	return (ft_strdup("machin"));
}

void	replace_key(char **input, ssize_t *key_coordinates, char *value)
{
	size_t	key_length;
	size_t	value_length;

	key_length = key_coordinates[1] - key_coordinates[0];
	value_length = ft_strlen(value);
	if (key_length >= value_length)
	{
		ft_memmove(*input + key_coordinates[0] + key_length, *input + key_coordinates[0] + value_length, ft_strlen(*input + key_coordinates[0] + value_length));
	}
}

void	expand_variable(char *input)
{
	ssize_t	key_coordinates[2];
	char	temp;
	char	*value;

	get_variable_key_coordinates(input, key_coordinates);
	if (key_coordinates[0] == -1)
		return ;
	temp = input[key_coordinates[1]];
	input[key_coordinates[1]] = '\0';
	value = envget(input + key_coordinates[0]);
	input[key_coordinates[1]] = temp;
	replace_key(&input, key_coordinates, value);
	free(value);
}
