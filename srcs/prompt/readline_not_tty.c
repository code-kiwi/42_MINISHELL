/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_not_tty.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 18:15:20 by root              #+#    #+#             */
/*   Updated: 2024/05/13 10:17:29 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "minishell.h"
#include "prompt.h"

static bool	increase_buffer_size(char **buffer,
	size_t previous_size, size_t new_size)
{
	char	*new_buffer;

	new_buffer = ft_calloc(new_size, sizeof(char));
	if (new_buffer == NULL)
		return (false);
	ft_memcpy(new_buffer, *buffer, previous_size * sizeof(char));
	free(*buffer);
	*buffer = new_buffer;
	return (true);
}

static bool	read_until_line_break(char **buffer, size_t buffer_size)
{
	int		rd;
	size_t	line_length;

	line_length = ft_strlen(*buffer);
	while (line_length < buffer_size - 1)
	{
		rd = read(STDIN_FILENO, *buffer + line_length, 1);
		if (rd == -1 || (line_length == 0 && rd == 0))
		{
			free(*buffer);
			*buffer = NULL;
			return (true);
		}
		if ((*buffer)[line_length] == '\n')
		{
			(*buffer)[line_length] = '\0';
			return (true);
		}
		if (rd == 0)
			return (true);
		line_length++;
	}
	return (false);
}

char	*readline_not_tty(void)
{
	char	*buffer;
	size_t	buffer_length;

	buffer = ft_calloc(READ_BUFFER_LENGTH, sizeof(char));
	if (buffer == NULL)
		return (NULL);
	buffer_length = READ_BUFFER_LENGTH;
	while (true)
	{
		if (read_until_line_break(&buffer, buffer_length))
			return (buffer);
		if (increase_buffer_size(&buffer, buffer_length,
				buffer_length + READ_BUFFER_LENGTH) == false)
		{
			free(buffer);
			return (NULL);
		}
		buffer_length += READ_BUFFER_LENGTH;
	}
	return (buffer);
}
