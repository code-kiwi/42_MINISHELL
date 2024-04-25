/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_list1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:37:09 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/25 11:38:59 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"
#include "execution.h"
#include "redirections.h"

/*
 *	Executes a redirection depending on its type
 *	Calls the right executor, providing it the redirection information
 *	The after_last_hd flag is used to know if we are making redirections after
 *	the last here_doc redirection or not in order to avoid infile redirections
 *	to overwrite a here_doc redirection
 */
static void	redirection_exec_dispatch(
	t_redirection *redirection, t_redirections_info *info, bool after_last_hd
)
{
	if (redirection == NULL)
		return ;
	if (redirection->type == REDIRECTION_TYPE_INFILE)
		exec_redirection_infile(redirection, info, after_last_hd);
	else if (
		redirection->type == REDIRECTION_TYPE_OUTFILE_TRUNC
		|| redirection->type == REDIRECTION_TYPE_OUTFILE_APPEND
	)
		exec_redirection_out(redirection, info);
}

/*
 *	Executes all the heredoc redirections from the given redirection list
 *	Returns the position (into the list) of the last heredoc redirection
 *	Returns -1 if no heredoc redirection has been encountered
 */
static ssize_t	exec_heredocs(t_list *redirections, t_redirections_info *info)
{
	ssize_t			position;
	ssize_t			last_hd_pos;
	t_redirection	*redirection;
	t_list			*current_red;

	if (redirections == NULL)
		return (-1);
	current_red = redirections;
	position = 0;
	last_hd_pos = -1;
	while (current_red != NULL)
	{
		redirection = (t_redirection *) current_red->content;
		if (redirection->type == REDIRECTION_TYPE_HEREDOC)
		{
			exec_redirection_heredoc(redirection, info);
			last_hd_pos = position;
		}
		position++;
		current_red = current_red->next;
	}
	return (last_hd_pos);
}

/*
 *	Executes all the redirections stored into the given redirection list
 *	Stores the redirection information into info member of redirection_list
 *	Steps:
 *		- executes all the heredoc redirections first
 *		- executes the other redirections (using last heredoc's index in order
 *		to make stdin redirections logical: from left to right)
 */
void	exec_redirection_list(t_redirection_list *redirection_list)
{
	t_list			*current;
	t_redirection	*redirection;
	ssize_t			position_last_heredoc;
	ssize_t			position;

	if (redirection_list == NULL)
		return ;
	current = redirection_list->redirections;
	position_last_heredoc = exec_heredocs(current, &(redirection_list->info));
	position = 0;
	while (current != NULL)
	{
		redirection = (t_redirection *) current->content;
		redirection_exec_dispatch(redirection, &(redirection_list->info), \
			(position_last_heredoc != -1 && position > position_last_heredoc));
		position++;
		current = current->next;
	}
}
