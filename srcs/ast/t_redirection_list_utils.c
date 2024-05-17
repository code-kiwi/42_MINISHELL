/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redirection_list_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:50:23 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/17 12:32:03 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

#include "libft.h"
#include "minishell.h"
#include "redirections.h"

/*
 *	Allocates a t_redirection_list and returns a pointer to it.
 *	The info member is set with default values
 *	The redirections (a list) member is set to NULL
 *	In case of ERROR, returns NULL
 */
t_redirection_list	*redirection_list_create(void)
{
	t_redirection_list	*redirs;

	redirs = (t_redirection_list *) ft_calloc(1, sizeof(t_redirection_list));
	if (redirs == NULL)
		return (NULL);
	redirs->info.fd_stdin = FD_UNSET;
	redirs->info.fd_stdout = FD_UNSET;
	redirs->info.error_infile = false;
	redirs->info.error_outfile = false;
	redirs->info.hdc_last_pos = -1;
	redirs->info.fdin_is_heredoc = false;
	redirs->info.hdc_needs_expansion = false;
	return (redirs);
}

/*
 *	Adds a new redirection to a t_redirection_list element
 *	The new redirection is allocated and added to the end of t_list redirections
 *	Returns true on SUCCESS
 *	Returns false on ERROR
 *	Error cases:
 *		- memory allocation
 *		- bad parameters given to the function
 *		- unhandled redirection operator
 */
bool	redirection_list_add(
	t_redirection_list *redirs, char *op, char *filename
)
{
	t_list			*new;
	t_redirection	*redirection;

	if (redirs == NULL || op == NULL || filename == NULL)
		return (false);
	redirection = redirection_create(op, filename);
	if (redirection == NULL)
		return (false);
	new = ft_lstnew((void *) redirection);
	if (new == NULL)
	{
		redirection_free((void *) redirection);
		return (false);
	}
	ft_lstadd_back(&(redirs->redirections), new);
	return (true);
}

/*
 *	Frees the memory allocated to a t_redirection_list element
 *	The redirections t_list element is cleaned
 *	The info member file descriptors are closed if necessary
 *	The initial pointer to the t_redirection_list is set to NULL
 */
void	redirection_list_free(t_redirection_list **redirs_ptr)
{
	t_redirection_list	*redirs;

	if (redirs_ptr == NULL || *redirs_ptr == NULL)
		return ;
	redirs = *redirs_ptr;
	if (redirs->redirections != NULL)
		ft_lstclear(&(redirs->redirections), redirection_free);
	if (redirs->info.fd_stdin != FD_UNSET)
		fd_close_and_reset(&(redirs->info.fd_stdin));
	if (redirs->info.fd_stdout != FD_UNSET)
		fd_close_and_reset(&(redirs->info.fd_stdout));
	free(redirs);
	*redirs_ptr = NULL;
}

/*
 *	Returns true if the given redirection list contains an error, else returns
 *	false
*/
bool	redirection_list_has_error(t_redirection_list *redirection_list)
{
	t_redirections_info	*info;

	if (redirection_list == NULL)
		return (false);
	info = &(redirection_list->info);
	return (
		info->error_infile || info->error_outfile
		|| info->fd_stdin == FD_ERROR || info->fd_stdout == FD_ERROR
	);
}
