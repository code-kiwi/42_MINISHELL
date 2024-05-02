/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 09:00:27 by root              #+#    #+#             */
/*   Updated: 2024/05/02 09:02:31 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	ft_getc(FILE *stream)
{
	char	c;

	if (stream == NULL)
		return (EOF);
	if (read(STDIN_FILENO, &c, 1) == -1)
		return (EOF);
	return (c);
}
