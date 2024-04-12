/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:28:30 by brappo            #+#    #+#             */
/*   Updated: 2024/04/12 10:28:52 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	add_word_token(t_list **head, char *str)
{
	t_token	*new_token;

	new_token = t_token_init(ft_strdup(str), WORD);
	if (lst_push_front_content(head, \
			new_token, t_token_free))
		return (true);
	return (false);
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
