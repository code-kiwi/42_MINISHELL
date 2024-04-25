/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_file_descriptor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:26:18 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/25 11:55:48 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

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
