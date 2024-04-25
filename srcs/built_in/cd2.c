/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:10:34 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/25 17:47:34 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "minishell.h"
#include "env.h"
#include "built_in.h"

int	bi_cd_execution(t_minishell *shell, char *path)
{
	if (shell == NULL || path == NULL)
		return (bi_cd_handle_error(CD_MSG_ERR_INTERNAL, EXIT_FAILURE, NULL));
	// Check if path exists
	// Get PWD
	// Set OLDPWD
	// Set new PWD
	// chdir
	free(path);
	return (EXIT_SUCCESS);
}
