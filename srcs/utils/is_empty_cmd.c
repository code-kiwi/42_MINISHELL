/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_empty_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:49:47 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/10 17:02:14 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "minishell.h"

/*
 *	Given a command, says if it is empty
 *	An empty command can be:
 *		- a NULL string
 *		- an empty string
 *		- a string composed entirely of spaces
 */
bool	utils_is_empty_cmd(char *cmd)
{
	return (cmd == NULL || *cmd == '\0' || string_contains_only_spaces(cmd));
}
