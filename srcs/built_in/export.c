/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:11:12 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/24 15:24:36 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_export(t_minishell *shell, char **argv)
{
	printf("CMD: export\n");
	if (shell || argv)
		return (0);
	return (0);
}
