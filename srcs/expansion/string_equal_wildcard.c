/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_equal_wildcard.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:39:55 by brappo            #+#    #+#             */
/*   Updated: 2024/04/25 11:44:32 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"

bool	is_wildcard(char *characters, t_list *wildcards)
{
	if (wildcards == NULL)
		return (false);
	if (characters == wildcards->content)
		return (true);
	if (wildcards->next == NULL)
		return (false);
	return (characters == wildcards->next->content);
}

static size_t	get_next_wildcard(char *str_wildcard, t_list *wildcards)
{
	size_t	length;

	length = 1;
	while (str_wildcard[length]
		&& !is_wildcard(str_wildcard + length, wildcards))
	{
		length++;
	}
	return (length);
}

static ssize_t	search_characters(char *characters, \
	size_t character_length, char *str, t_list **wildcards)
{
	ssize_t	char_pos;

	char_pos = 0;
	if (is_wildcard(characters, *wildcards))
	{
		*wildcards = (*wildcards)->next;
		while (ft_strncmp(characters + 1, str + char_pos, \
				character_length - 1))
		{
			if (str[char_pos] == '\0')
				return (-1);
			char_pos++;
		}
		char_pos += character_length - 1;
	}
	else
	{
		if (ft_strncmp(characters, str, character_length))
			return (-1);
		char_pos += character_length;
	}
	return (char_pos);
}

bool	string_equal_wildcard(char *str_wildcard,
	char *str_b, t_list *wildcards)
{
	size_t	next_wildcard;
	ssize_t	char_pos;

	if (str_wildcard == NULL || str_b == NULL)
		return (str_wildcard == str_b);
	if (wildcards == NULL)
		return (ft_strcmp(str_wildcard, str_b) == 0);
	while (*str_wildcard)
	{
		if (is_wildcard(str_wildcard, wildcards) && !str_wildcard[1])
			return (true);
		next_wildcard = get_next_wildcard(str_wildcard, wildcards);
		char_pos = search_characters(str_wildcard, \
				next_wildcard, str_b, &wildcards);
		if (char_pos == -1)
			return (false);
		str_b += char_pos;
		str_wildcard += next_wildcard;
	}
	if (!is_wildcard(str_wildcard, wildcards) && *str_b)
		return (false);
	return (true);
}