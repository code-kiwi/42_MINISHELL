/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:28:30 by brappo            #+#    #+#             */
/*   Updated: 2024/04/25 11:43:26 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
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
		if (file->d_name[0] != '.'
			&& string_equal_wildcard(str, file->d_name, wildcards)
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
