/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:39:55 by brappo            #+#    #+#             */
/*   Updated: 2024/04/12 09:39:17 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	add_word_token(t_list **head, char *str)
{
	t_token	*new_token;

	new_token = t_token_init(ft_strdup(str), WORD);
	if (lst_push_front_content(head,
			new_token, t_token_free))
		return (true);
	return (false);
}

static size_t	get_character_end(char *str_wildcard)
{
	size_t	length;

	length = 1;
	while (str_wildcard[length] && str_wildcard[length] != '*')
		length++;
	return (length);
}

static ssize_t	search_characters(char *str_wildcard,
	size_t character_end, char *str_b)
{
	ssize_t	char_pos;

	char_pos = 0;
	if (*str_wildcard == '*')
	{
		while (ft_strncmp(str_wildcard + 1, str_b + char_pos,
				character_end - 1))
		{
			if (str_b[char_pos] == '\0')
				return (-1);
			char_pos++;
		}
		char_pos += character_end;
	}
	else
	{
		if (ft_strncmp(str_wildcard, str_b, character_end))
			return (-1);
		char_pos += character_end - 1;
	}
	return (char_pos);
}

bool	string_equal_wildcard(char *str_wildcard, char *str_b)
{
	size_t	character_end;
	ssize_t	char_pos;

	if (str_wildcard == NULL || str_b == NULL)
		return (str_wildcard == str_b);
	while (*str_wildcard)
	{
		if (str_wildcard[0] == '*' && !str_wildcard[1])
			return (true);
		character_end = get_character_end(str_wildcard);
		char_pos = search_characters(str_wildcard, character_end, str_b);
		if (char_pos == -1)
			return (false);
		str_b += char_pos;
		str_wildcard += character_end;
	}
	if (*str_wildcard != '*' && *str_b)
		return (false);
	return (true);
}

t_list	*expand_wildcard(char *str)
{
	DIR				*current_directory;
	struct dirent	*file;
	t_list			*result;

	current_directory = opendir(".");
	if (current_directory == NULL)
		return (NULL);
	result = NULL;
	file = readdir(current_directory);
	if (file == NULL)
		return (NULL);
	while (file != NULL)
	{
		if (file->d_name[0] != '.' && string_equal_wildcard(str, file->d_name))
		{
			if (!add_word_token(&result, file->d_name))
				return (ft_lstclear(&result, t_token_free), NULL);
		}
		file = readdir(current_directory);
	}
	closedir(current_directory);
	if (result == NULL)
		add_word_token(&result, str);
	return (result);
}
