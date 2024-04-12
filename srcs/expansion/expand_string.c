/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:12:32 by brappo            #+#    #+#             */
/*   Updated: 2024/04/12 14:35:19 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	remove_quote(char *input, bool value, size_t *index)
{
	if (*input != '\'' && *input != '"')
		return (value);
	ft_memmove(input, input + 1, ft_strlen(input));
	*index -= 1;
	return (!value);
}

static bool	jump(size_t *current_index, ssize_t character_to_jump)
{
	if (character_to_jump < 0)
		return (false);
	*current_index += character_to_jump - 1;
	return (true);
}

bool	quote_removal(char **input, t_minishell *shell, t_list **wildcards_pos)
{
	size_t	index;
	bool	single_quoted;
	bool	double_quoted;
	ssize_t	var_length;

	single_quoted = false;
	double_quoted = false;
	if (input == NULL || *input == NULL || wildcards_pos == NULL)
		return (false);
	index = 0;
	*wildcards_pos = NULL;
	while ((*input)[index] != '\0')
	{
		if ((*input)[index] == '\'' && !double_quoted)
			single_quoted = remove_quote(*input + index, single_quoted, &index);
		else if ((*input)[index] == '\"' && !single_quoted)
			double_quoted = remove_quote(*input + index, double_quoted, &index);
		else if ((*input)[index] == '$' && !single_quoted)
		{
			var_length = expand_variable(input, index, double_quoted, shell);
			if (!jump(&index, var_length))
				return (false);
		}
		else if ((*input)[index] == '*' && !single_quoted && !double_quoted)
		{
			if (!lst_push_front_content(wildcards_pos, *input + index, NULL))
				return (ft_lstclear(wildcards_pos, NULL), false);
		}
		index++;
	}
	return (true);
}

bool	expand_string(char **input, t_minishell *shell)
{
	t_list	*wildcards_pos;
	t_list	*files;

	if (quote_removal(input, shell, &wildcards_pos) == false)
		return (false);
	if (wildcards_pos != NULL)
	{
		files = expand_wildcard(*input, wildcards_pos);
		if (files == NULL)
		{
			ft_lstclear(&wildcards_pos, NULL);
			return (false);
		}
		ft_lstprint(files, print_token);
		ft_lstclear(&files, t_token_free);
		ft_lstclear(&wildcards_pos, NULL);
	}
	return (true);
}
