/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:10:14 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/24 15:24:59 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_unset(t_minishell *shell, char **argv)
{
	printf("CMD: unset\n");
	if (shell || argv)
		return (0);
	return (0);
}
