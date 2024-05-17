/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_expand_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:34:46 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/17 10:59:24 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "minishell.h"
#include "redirections.h"


#include <stdio.h>
void    exec_expand_heredoc(t_minishell *shell, t_redirection_list *redir_list)
{
    if (
        shell == NULL || redir_list == NULL
        || redirection_list_has_error(redir_list)
    )
        return ;
    printf("IS_HEREDOC: %d - NEEDS EXPANSION: %d\n", redir_list->info.in_is_heredoc, redir_list->info.hdc_needs_expansion);
}