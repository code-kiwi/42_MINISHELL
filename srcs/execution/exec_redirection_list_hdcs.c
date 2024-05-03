/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_list_hdcs.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:35:13 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/03 16:11:53 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"
#include "redirections.h"
#include "execution.h"

void	exec_redirection_list_heredocs(
	t_redirection_list *redirection_list, t_heredoc_exec_info *hdc_info
)
{
	t_list			*redir_link;
	t_redirection	*redir;

	if (hdc_info == NULL || redirection_list == NULL)
		return (hdc_info_set_error(hdc_info));
	redir_link = redirection_list->redirections;
	while (redir_link != NULL)
	{
		redir = (t_redirection *) redir_link->content;
		redir_link = redir_link->next;
		if (redir == NULL || redir->type != REDIRECTION_TYPE_HEREDOC)
			continue ;
		ft_printf("LIM: %s\n", redir->filename);
	}
}
