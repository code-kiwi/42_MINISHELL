/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redirection_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:32:34 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/10 16:55:38 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "minishell.h"
#include "redirections.h"

/*
 *	Returns the type of redirection accordig to the given operator
 *	If the operator is not handled, REDIRECTION_TYPE_ERROR is returned
 */
static enum e_redirection_type	redirection_get_type(char *operator)
{
	if (operator == NULL)
		return (REDIRECTION_TYPE_ERROR);
	if (ft_strcmp(operator, DLESS) == 0)
		return (REDIRECTION_TYPE_HEREDOC);
	if (ft_strcmp(operator, LESS) == 0)
		return (REDIRECTION_TYPE_INFILE);
	if (ft_strcmp(operator, GREAT) == 0)
		return (REDIRECTION_TYPE_OUTFILE_TRUNC);
	if (ft_strcmp(operator, DGREAT) == 0)
		return (REDIRECTION_TYPE_OUTFILE_APPEND);
	return (REDIRECTION_TYPE_ERROR);
}

/*
 *	Allocates a t_redirection element and returns a pointer to it
 *	The type member is set according to the given operator
 *	The filname member is a duplicated string from filename input
 *	In case of ERROR, returns NULL
 *	Error cases:
 *		- wrong inputs
 *		- operator not handled
 *		- memory allocation fail
 */
t_redirection	*redirection_create(char *operator, char *filename)
{
	t_redirection			*redirection;
	enum e_redirection_type	type;

	if (operator == NULL || filename == NULL)
		return (NULL);
	type = redirection_get_type(operator);
	if (operator == REDIRECTION_TYPE_ERROR)
		return (NULL);
	redirection = (t_redirection *) ft_calloc(1, sizeof(t_redirection));
	if (redirection == NULL)
		return (NULL);
	redirection->type = type;
	redirection->filename = ft_strdup(filename);
	if (redirection->filename == NULL)
	{
		redirection_free(&redirection);
		return (NULL);
	}
	return (redirection);
}

/*
 *	Frees the memory allocated to a t_redirection element
 *	The filename component, if it is set, is freed
 *	NOTE: This function takes a void * pointer in order to enable the use of
 *	ft_lstclear() because t_redirection elements are saved into a t_list.
 */
void	redirection_free(void *redirection_ptr)
{
	t_redirection	*redirection;

	if (redirection_ptr == NULL)
		return ;
	redirection = (t_redirection *) redirection_ptr;
	if (redirection->filename != NULL)
		free(redirection->filename);
	free(redirection);
}
