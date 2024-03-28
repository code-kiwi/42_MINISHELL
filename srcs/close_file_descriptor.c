/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_file_descriptor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:26:18 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/28 12:30:49 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_file_descriptor(int fd)
{
	if (fd > 0 && close(fd) == -1)
		handle_error(NULL, ERROR_MSG_CLOSE, 0);
}
