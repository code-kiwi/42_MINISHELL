/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_equal_wildcard.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:39:55 by brappo            #+#    #+#             */
/*   Updated: 2024/05/14 10:22:36 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "minishell.h"
#include "libft.h"

static bool	is_wildcard(char *wildcard_addr, t_list *wildcards)
{
	if (wildcards == NULL)
		return (false);
	return (wildcard_addr == wildcards->content);
}

static bool	string_equal_wildcard_recursive(char *str_wildcard,
	char *str_b, t_list *wildcards)
{
	while (*str_wildcard)
	{
		if (is_wildcard(str_wildcard, wildcards))
		{
			if (string_equal_wildcard_recursive(str_wildcard + 1,
					str_b, wildcards->next))
				return (true);
			if (*str_b && string_equal_wildcard_recursive(str_wildcard,
					str_b + 1, wildcards))
				return (true);
			return (false);
		}
		if (*str_b != *str_wildcard)
			return (false);
		str_b++;
		str_wildcard++;
	}
	return (*str_b == '\0' && *str_wildcard == '\0');
}

bool	string_equal_wildcard(char *str_wildcard,
	char *str_b, t_list *wildcards)
{
	if (str_b == NULL || str_wildcard == NULL)
		return (str_b == str_wildcard);
	if (wildcards == NULL)
		return (string_equals(str_wildcard, str_b));
	return (string_equal_wildcard_recursive(str_wildcard,
			str_b, wildcards));
}
