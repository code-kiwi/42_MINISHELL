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

	word_str = (char *)word;
	prefix_str = (char *)prefix;
	return (ft_strstr(word_str, prefix_str) == word);
}