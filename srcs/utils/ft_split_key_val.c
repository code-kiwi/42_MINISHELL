/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_key_val.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 09:58:22 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/17 09:26:20 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include "libft.h"

/*
 *	Splits the given str into two pieces using the key delimitor
 *	Returns a NULL terminated array containing the two pieces
 *	If the key has not been found, returns an array containing only one
 *	string: an str duplicate
 *	If str is NULL or empty, returns an empty array
 *	In case of error, returns NULL
*/
char	**ft_split_key_val(char *str, char *key)
{
	char	*key_location;
	char	**res;

	res = (char **) ft_calloc(3, sizeof(char *));
	if (res == NULL)
		return (NULL);
	if (str == NULL || *str == '\0')
		return (res);
	key_location = ft_strstr(str, key);
	if (key == NULL || key_location == NULL)
	{
		res[0] = ft_strdup(str);
		if (res[0] == NULL && errno != 0)
			return (ft_free_str_array(&res), NULL);
		return (res);
	}
	res[0] = ft_substr(str, 0, key_location - str);
	res[1] = ft_strdup(key_location + ft_strlen(key));
	if ((res[0] == NULL && errno != 0) || (res[1] == NULL && errno != 0))
		return (ft_free_str_array(&res), NULL);
	return (res);
}
