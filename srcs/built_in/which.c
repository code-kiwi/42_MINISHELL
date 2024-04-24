/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:09:49 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/24 15:25:10 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_which(t_minishell *shell, char **argv)
{
	printf("CMD: which\n");
	if (shell || argv)
		return (0);
	return (0);
}
