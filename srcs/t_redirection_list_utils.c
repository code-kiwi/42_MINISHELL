/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redirection_list_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:50:23 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/28 13:35:31 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Allocates a t_redirection_list and returns a pointer to it.
 *	The info member is set with default values
 *	The redirections (a list) member is set to NULL
 *	In case of ERROR, returns NULL
 */
t_redirection_list	*create_redirection_list(void)
{
	t_redirection_list	*redirs;

	redirs = (t_redirection_list *) ft_calloc(1, sizeof(t_redirection_list));
	if (redirs == NULL)
		return (NULL);
	redirs->info.fd_stdin = FD_UNSET;
	redirs->info.fd_stdout = FD_UNSET;
	redirs->info.error_infile = false;
	redirs->info.error_outfile = false;
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
bool	add_redirection(t_redirection_list *redirs, char *op, char *filename)
{
	t_list			*new;
	t_redirection	*redirection;

	if (redirs == NULL || op == NULL || filename == NULL)
		return (false);
	redirection = create_redirection(op, filename);
	if (redirection == NULL)
		return (false);
	new = ft_lstnew((void *) redirection);
	if (new == NULL)
	{
		free_redirection((void *) redirection);
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
void	free_redirection_list(t_redirection_list **redirs_ptr)
{
	t_redirection_list	*redirs;

	if (redirs_ptr == NULL || *redirs_ptr == NULL)
		return ;
	redirs = *redirs_ptr;
	if (redirs->redirections != NULL)
		ft_lstclear(&(redirs->redirections), free_redirection);
	if (redirs->info.fd_stdin != FD_UNSET)
		close_file_descriptor(redirs->info.fd_stdin);
	if (redirs->info.fd_stdout != FD_UNSET)
		close_file_descriptor(redirs->info.fd_stdout);
	free(redirs);
	*redirs_ptr = NULL;
}
