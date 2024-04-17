/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:28:30 by brappo            #+#    #+#             */
/*   Updated: 2024/04/17 10:58:17 by brappo           ###   ########.fr       */
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
			&& string_equal_wildcard(str, file->d_name, wildcards))
		{
			if (!add_token(&result, file->d_name, WORD))
				return (ft_lstclear(&result, t_token_free), NULL);
		}
		file = readdir(current_directory);
	}
	closedir(current_directory);
	if (result == NULL)
		add_token(&result, str, WORD);
	return (result);
}
