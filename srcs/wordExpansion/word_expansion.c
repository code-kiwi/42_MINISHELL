/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 08:34:50 by brappo            #+#    #+#             */
/*   Updated: 2024/04/04 11:08:40 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t	find_bracket(char *input, ssize_t variable_start)
{
	char	*closing_bracket;

	closing_bracket = ft_strchr(input + variable_start, '}');
	if (closing_bracket == NULL)
		return (-1);
	return (closing_bracket - input);
}

ssize_t	end_of_name(char *input, ssize_t variable_start)
{
	ssize_t	index;

	index = variable_start;
	while (input[index] != '\0')
	{
		if (!ft_isalnum(input[index])
			&& input[index] != '_')
			break;
		index++;
	}
	return (index);
}

void	get_variable(char *input)
{
	ssize_t	variable_end;
	ssize_t	variable_start;
	char	temp;

	if (input == NULL || *input != '$')
		return ;
	variable_start = 1;
	if (input[variable_start] == '{')
	{
		variable_start++;
		variable_end = find_bracket(input, variable_start);
	}
	else
		variable_end = end_of_name(input, variable_start);
	if (variable_end == -1)
		return ;
	temp = input[variable_end];
	input[variable_end] = '\0';
	printf("%s", input + variable_start);
	input[variable_end] = temp;
}
