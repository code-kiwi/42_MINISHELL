/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:28:30 by brappo            #+#    #+#             */
/*   Updated: 2024/04/18 12:03:21 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (file == NULL)
		return (NULL);
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
	return (result);
}
