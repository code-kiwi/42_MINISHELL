/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_node_logical_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:24:24 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/10 16:55:09 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "node.h"

t_node_logical	*node_logical_create(void)
{
	t_node_logical	*node_logic;

	node_logic = (t_node_logical *) malloc(sizeof(t_node_logical));
	if (node_logic == NULL)
		return (NULL);
	fds_init(node_logic->child_right_fds);
	return (node_logic);
}

void	node_logical_free(void **node_ptr)
{
	t_node_logical	*node_logic;

	if (node_ptr == NULL || *node_ptr == NULL)
		return ;
	node_logic = (t_node_logical *) *node_ptr;
	fds_close_and_reset(node_logic->child_right_fds);
	free(node_logic);
	*node_ptr = NULL;
}
