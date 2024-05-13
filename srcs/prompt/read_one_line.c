/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_one_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:05:38 by root              #+#    #+#             */
/*   Updated: 2024/05/13 22:11:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "minishell.h"
#include "libft.h"

static char	*extract_first_line(char **lines)
{
	char	*input;

	input = lines[0];
	ft_memmove(lines, lines + 1, array_size((void **)lines) * sizeof(char *));
	return (input);
}

static void	free_and_reset(void **malloced_str)
{
	free(*malloced_str);
	*malloced_str = NULL;
}

char	*read_one_line(char *prompt)
{
	static char	**lines = NULL;
	char		*input;

	if (prompt == NULL)
	{
		ft_free_str_array(&lines);
		return (NULL);
	}
	if (lines != NULL)
	{
		if (lines[0] != NULL)
			return (extract_first_line(lines));
		else
			free_and_reset((void **)&lines);
	}
	input = readline(prompt);
	if (ft_strchr(input, '\n'))
	{
		lines = ft_split(input, "\n");
		free(input);
		if (lines == NULL)
			return (NULL);
		input = extract_first_line(lines);
	}
	return (input);
}
