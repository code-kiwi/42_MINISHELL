/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:26:15 by brappo            #+#    #+#             */
/*   Updated: 2024/04/02 18:44:46 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_prefix(void	*word, void *prefix)
{
	char	*word_str;
	char	*prefix_str;

	word_str = (char *)word;
	prefix_str = (char *)prefix;
	return (ft_strstr(word_str, prefix_str) == word);
}

char	*join_into_dest(char **dest, char *str)
{
	char	*temp;

	temp = ft_strjoin(*dest, str);
	if (temp == NULL)
		return (NULL);
	free(*dest);
	*dest = temp;
	return (temp);
}
