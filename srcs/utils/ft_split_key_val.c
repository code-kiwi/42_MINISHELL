/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_key_val.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 09:58:22 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/25 11:57:44 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include "libft.h"

/*
 *	Tests if str has the valid form: "<KEY><SEP><VALUE>"
 *	Returns true if it is ok, else returns false
 */
static bool	is_valid_key_val_str(char *str, char sep)
{
	char	*sep_location;

	if (str == NULL)
		return (false);
	sep_location = ft_strchr(str, sep);
	if (sep_location == NULL || sep_location == str)
		return (false);
	return (true);
}

/*
 *	Do split the str into key/value pieces stored into the res given array
 *	In case of ERROR, returns NULL (and sets errno)
 */
static char	**process_key_val_split(char *str, char sep, char **res)
{
	char	*sep_location;

	if (str == NULL || res == NULL)
	{
		errno = EINVAL;
		return (NULL);
	}
	sep_location = ft_strchr(str, sep);
	if (sep_location == NULL)
	{
		errno = EINVAL;
		return (NULL);
	}
	res[0] = ft_substr(str, 0, sep_location - str);
	res[1] = ft_strdup(sep_location + 1);
	if (res[0] == NULL || res[1] == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	return (res);
}

/*
 *	Splits str into two pieces: a key and value stored in a NULL teminated array
 *	Returns a pointer to this array, result from: [[<KEY>], [<VAL>], NULL]
 *	Input str for expected: "<KEY><SEP><VALUE>"
 *	The <VALUE> str can contain zero or more sep characters, the split stops at
 *	the first one.
 *	In case of ERROR, returns NULL (and sets errno)
 */
char	**ft_split_key_val(char *str, char sep)
{
	char	**res;

	if (str == NULL || !is_valid_key_val_str(str, sep))
	{
		errno = EINVAL;
		return (NULL);
	}
	res = (char **) ft_calloc(3, sizeof(char *));
	if (res == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	if (process_key_val_split(str, sep, res) == NULL)
	{
		ft_free_str_array(&res);
		return (NULL);
	}
	return (res);
}
