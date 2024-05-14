/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_is_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:46:37 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/14 09:48:31 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <sys/stat.h>
#include <errno.h>

/*
 *	Returns true if the given path is a directory, else returns false
 *	In case of ERROR, returns false
 *	NB: when an error is encountered, errno is reset to 0
 */
bool	path_is_dir(char *path)
{
	struct stat	file_info;

	if (stat(path, &file_info) == -1)
	{
		errno = 0;
		return (false);
	}
	if (S_ISDIR(file_info.st_mode))
		return (true);
	return (false);
}
