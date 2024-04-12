/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilrdcards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:39:55 by brappo            #+#    #+#             */
/*   Updated: 2024/04/11 12:58:06y brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_character_end(char *str_wildcard)
{
	size_t	length;

	length = 1;
	while (str_wildcard[length] && str_wildcard[length] != '*')
		length++;
	return (length);
}

bool	string_equal_wildcard(char *str_wildcard, char *str_b)
{
	size_t	character_end;

	if (str_wildcard == NULL || str_b == NULL)
		return (str_wildcard == str_b);
	while (*str_wildcard)
	{
		character_end = get_character_end(str_wildcard);
		if (*str_wildcard == '*')
		{
			if (!str_wildcard[1])
				return (true);
			while (ft_strncmp(str_wildcard + 1, str_b, character_end - 1))
			{
				if (*str_b == '\0')
					return (false);
				str_b++;
			}
			str_b--;
		}
		else if (ft_strncmp(str_wildcard, str_b, character_end))
			return (false);
		str_wildcard += character_end;
		str_b += character_end;
	}
	if (*str_wildcard != '*' && *str_b)
		return (false);
	return (true);
}

char	*expand_wildcard(char *str)
{
	DIR				*current_directory;
	struct dirent	*file;
	t_list			*result;

	current_directory = opendir(".");
	if (current_directory == NULL)
		return (NULL);
	result = NULL;
	file = readdir(current_directory);
	while (file != NULL)
	{
		if (file->d_name[0] != '.' && string_equal_wildcard(str, file->d_name))
		{
			lst_push_front_content(&result, t_token_init(), t_token_free);
		}
		file = readdir(current_directory);
	}
	closedir(current_directory);
	if (result == NULL)
		return (ft_strdup(str));
	return (result);
}
