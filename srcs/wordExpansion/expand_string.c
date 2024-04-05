/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:12:32 by brappo            #+#    #+#             */
/*   Updated: 2024/04/05 16:14:34 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	remove_quote(char *input, bool value, size_t *index)
{
	if (*input != '\'' && *input != '"')
		return (value);
	ft_memmove(input, input + 1, ft_strlen(input));
	*index -= 1;
	return (!value);
}

bool	jump(size_t *current_index, ssize_t character_to_jump)
{
	if (character_to_jump < 0)
		return (false);
	*current_index += character_to_jump - 1;
	return (true);
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
			single_quoted = remove_quote(*input + index, single_quoted, &index);
		else if ((*input)[index] == '\"' && !single_quoted)
			double_quoted = remove_quote(*input + index, double_quoted, &index);
		else if ((*input)[index] == '$' && !single_quoted)
		{
			variable_length = expand_variable(input, index, double_quoted);
			if (!jump(&index, variable_length))
				return (false);
		}
		index++;
	}
	return (true);
}
