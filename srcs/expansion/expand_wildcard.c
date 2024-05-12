/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:28:30 by brappo            #+#    #+#             */
/*   Updated: 2024/05/12 19:53:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

#include "libft.h"
#include "token.h"
#include "expansion.h"

static int	alphabetic_compare(void *a, void *b)
{
	size_t	index;
	char	character_a;
	char	character_b;

	index = 0;
	if (a == NULL || b == NULL)
		return (a - b);
	character_a = *(char *)a;
	character_b = *(char *)b;
	while (character_a)
	{
		if (character_a >= 65 && character_a <= 90)
			character_a += 32;
		if (character_b >= 65 && character_b <= 90)
			character_b += 32;
		if (character_a != character_b)
			return (character_a - character_b);
		character_a = *(char *)(a + index);
		character_b = *(char *)(b + index);
		index++;
	}
	return (0);
}

bool	file_match(struct dirent *file, t_list *wildcards, char *str)
{
	bool		match;
	struct stat	file_stat;
	char		*path;

	// if (file->d_name[0] == '.' && str[0] != '.')
	// 	return (false);
	match = string_equal_wildcard(str, file->d_name, wildcards);
	// if (match)
	// 	return (true);
	// path = ft_strjoin("./", file->d_name); 
	// if (path == NULL)
	// 	return (false);
	// // stat(path, &file_stat);
	// free(path);
	// if (!S_ISDIR(file_stat.st_mode))
	// 	return (false);
	// path = ft_strjoin(file->d_name, "/");
	// if (path == NULL)
	// 	return (false);
	// match = string_equal_wildcard(str, path, wildcards);
	// free(str);
	return (match);
}

t_list	*expand_wildcard(char *str, t_list *wildcards)
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
		if (file_match(file, wildcards, str)
			&& !lst_push_front_content(&result, ft_strdup(file->d_name), free))
		{
			closedir(current_directory);
			ft_lstclear(&result, free);
			return (NULL);
		}
		file = readdir(current_directory);
	}
	closedir(current_directory);
	return (lst_sort(&result, alphabetic_compare));
}
