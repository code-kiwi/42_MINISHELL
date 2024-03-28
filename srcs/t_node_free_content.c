/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_node_free_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:44:06 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/28 10:21:07 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Frees the memory allocated to a t_node_command
 *	Frees its argv component (frees all the strings contained in this argv)
 *	Frees the redirection component
 *	Frees the t_node_command itself and sets the pointer to NULL
 */
void	free_node_content_command(void **node_ptr)
{
	t_node_command	*node;

	if (node_ptr == NULL || *node_ptr == NULL)
		return ;
	node = (t_node_command *) *node_ptr;
	while (--node->argc)
		free((node->argv)[node->argc]);
	free(node->argv);
	free_redirection(&(node->redirections));
	free(node);
	*node_ptr = NULL;
}

/*
 *	Frees the memory allocated to a t_node_pipe
 *	Frees its argv component (frees all the strings contained in this argv)
 *	Frees the redirection component
 *	Frees the t_node_command itself and sets the pointer to NULL
 */
void	free_node_content_pipe(void **node_ptr)
{
	t_node_pipe	*node;

	if (node_ptr == NULL || *node_ptr == NULL)
		return ;
	node = (t_node_pipe *) *node_ptr;
	free(node);
	*node_ptr = NULL;
}
