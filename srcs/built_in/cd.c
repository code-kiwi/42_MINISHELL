/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:10:34 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/25 12:42:02 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

int	bi_cd(t_minishell *shell, char **argv)
{
	printf("CMD: cd\n");
	if (shell || argv)
		return (0);
	return (0);
}