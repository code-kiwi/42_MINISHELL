/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redirection_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:50:23 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/28 09:33:27 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Allocates a redirection and returns a pointer to it.
 *	All the members are set to NULL.
 */
static t_redirection	*create_empty_redirection(void)
{
	t_redirection	*redirection;

	redirection = (t_redirection *) malloc(sizeof(t_redirection));
	if (redirection == NULL)
		return (NULL);
	ft_memset(redirection, 0, sizeof(t_redirection));
	return (redirection);
}

/*
 *	Allocates a redirection and returns a pointer to it.
 *	The passed arguments are duplicated in order to have fresh pointers to
 *	the components of the redirection.
 *	In case of error, frees the redirection and returns NULL.
 */
t_redirection	*create_redirection(
	char *here_doc, char *infile, char *outfile_append, char *outfile_truncate
)
{
	t_redirection	*redirection;

	redirection = create_empty_redirection();
	if (redirection == NULL)
		return (NULL);
	redirection->here_doc = ft_strdup(here_doc);
	redirection->infile = ft_strdup(infile);
	redirection->outfile_append = ft_strdup(outfile_append);
	redirection->outfile_truncate = ft_strdup(outfile_truncate);
	if (
		(redirection->here_doc == NULL && here_doc != NULL)
		|| (redirection->infile == NULL && infile != NULL)
		|| (redirection->outfile_append == NULL && outfile_append != NULL)
		|| (redirection->outfile_truncate == NULL && outfile_truncate != NULL)
	)
	{
		free_redirection(&redirection);
		return (NULL);
	}
	return (redirection);
}

/*
 *	Frees the memory of a redirection and of all its components.
 *	Sets the redirection pointer to NULL.
 */
void	free_redirection(t_redirection **redirection_ptr)
{
	t_redirection	*redirection;

	if (redirection_ptr == NULL || *redirection_ptr == NULL)
		return ;
	redirection = *redirection_ptr;
	if (redirection->here_doc != NULL)
		free(redirection->here_doc);
	if (redirection->infile != NULL)
		free(redirection->infile);
	if (redirection->outfile_append != NULL)
		free(redirection->outfile_append);
	if (redirection->outfile_truncate != NULL)
		free(redirection->outfile_truncate);
	free(redirection);
	*redirection_ptr = NULL;
}
