/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 02:23:50 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/01 02:29:02 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"

/*
 *	Returns true if the given string contains only spaces, else returns false
 *	If the string is NULL, returns false
 */
bool	string_contains_only_spaces(char *str)
{
	if (str == NULL)
		return (false);
	while (*str != '\0')
	{
		if (!ft_isspace(*str))
			return (false);
		str++;
	}
	return (true);
}
