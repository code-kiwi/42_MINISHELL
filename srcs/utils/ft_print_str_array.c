/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:02:21 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/04 14:05:27 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Prints a NULL terminated array of strings
 */
void	ft_print_str_array(char **array)
{
	if (array == NULL)
		return ;
	if (*array == NULL)
	{
		printf("STR_Array is empty...\n");
		return ;
	}
	while (*array != NULL)
	{
		printf("STR: \"%s\"\n", *array);
		++array;
	}
}
