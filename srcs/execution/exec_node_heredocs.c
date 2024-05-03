/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node_heredocs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:11:13 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/03 16:12:46 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "execution.h"
#include "node.h"

static t_redirection_list	*get_node_redirs(t_node *node)
{
	t_node_command	*node_cmd;
	t_node_subshell	*node_sub;

	if (
		node == NULL || node->content == NULL
		|| (node->type != NODE_COMMAND && node->type != NODE_SUBSHELL)
	)
		return (NULL);
	if (node->type == NODE_COMMAND)
	{
		node_cmd = (t_node_command *) node->content;
		return (node_cmd->redirection_list);
	}
	if (node->type == NODE_SUBSHELL)
	{
		node_sub = (t_node_subshell *) node->content;
		return (node_sub->redirection_list);
	}
	return (NULL);
}

void	exec_node_hdcs(t_node *node, t_heredoc_exec_info *hdc_info)
{
	t_redirection_list	*redirs;

	if (hdc_info == NULL || hdc_info->error_flag || hdc_info->interruption)
		return ;
	if (
		node == NULL || node->content == NULL
		|| (node->type != NODE_COMMAND && node->type != NODE_SUBSHELL)
	)
		return (hdc_info_set_error(hdc_info));
	redirs = get_node_redirs(node);
	if (redirs == NULL)
		return (hdc_info_set_error(hdc_info));
	exec_redirection_list_heredocs(redirs, hdc_info);
}
