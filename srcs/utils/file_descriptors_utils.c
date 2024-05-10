/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:26:18 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/10 17:02:01 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "minishell.h"

/*
 *	Returns true is the given file descriptor corresponds to a valid integer,
 *	else returns false
 *	NB: does not check if the fd corresponds to an opened file, only checks if
 *	the fd value is not FD_ERROR or FD_UNSET
 */
bool	is_fd_ok(int fd)
{
	return (fd != FD_ERROR && fd != FD_UNSET);
}

/*
 *	Initializes the values of an array of two integers to FD_UNSET value
 */
void	fds_init(int fds[2])
{
	if (fds == NULL)
		return ;
	fds[0] = FD_UNSET;
	fds[1] = FD_UNSET;
}

/*
 *	Closes and resets the values of an array of two integers to FD_UNSET value
 */
void	fds_close_and_reset(int fds[2])
{
	if (fds == NULL)
		return ;
	fd_close_and_reset(&(fds[0]));
	fd_close_and_reset(&(fds[1]));
}

/*
 *	Closes the given file descriptor, prompting an error if close fails
 *	Sets the given pointer to FD_UNSET
 */
void	fd_close_and_reset(int *fd)
{
	if (fd == NULL || *fd < 0)
		return ;
	fd_close(*fd);
	*fd = FD_UNSET;
}

/*
 *	Closes the given file descriptor, prompting an error if close fails
 */
void	fd_close(int fd)
{
	if (fd >= 0 && close(fd) == -1)
		handle_error(NULL, ERROR_MSG_CLOSE, 0);
}
