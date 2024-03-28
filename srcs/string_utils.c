/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:26:15 by brappo            #+#    #+#             */
/*   Updated: 2024/03/28 11:23:06 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_prefix(void	*word, void *prefix)
{
	char	*word_str;
	char	*prefix_str;
	int		diff;

	word_str = (char *)word;
	prefix_str = (char *)prefix;
	diff = ft_strncmp(word_str, prefix_str, ft_strlen(prefix_str));
	if (diff == 0)
		return (true);
	return (false);
}
