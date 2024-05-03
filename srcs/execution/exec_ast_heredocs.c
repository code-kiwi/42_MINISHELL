/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_heredocs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:54:05 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/03 15:31:34 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "minishell.h"
#include "node.h"
#include "execution.h"

/*
 *	Given a node and heredoc_info, browses the AST binary tree (Depth First Sch)
 *	and executes each node's heredoc redirections
 *	If the node is a SUBSHELL one:
 *		- executes the heredocs of the subshell's AST member
 *		- executes the subshell node's heredocs
 *	NB: This function is recursive, it stops if hdc_info requires it, if the
 *	given node is NULL or if hdc_info is invalid
 */
static void	exec_ast_hdcs_process(t_node *node, t_heredoc_exec_info *hdc_info)
{
	t_node_subshell	*node_sub;

	if (
		node == NULL || hdc_info == NULL
		|| hdc_info->error_flag || hdc_info->interruption
	)
		return ;
	if (
		node->type == NODE_PIPE || node->type == NODE_AND
		|| node->type == NODE_OR
	)
	{
		exec_ast_hdcs_process(node->child_left, hdc_info);
		exec_ast_hdcs_process(node->child_right, hdc_info);
	}
	else if (node->type == NODE_COMMAND)
		exec_node_hdcs(node, hdc_info);
	else if (node->type == NODE_SUBSHELL)
	{
		node_sub = (t_node_subshell *) node->content;
		exec_ast_hdcs_process(node_sub->ast, hdc_info);
		exec_node_hdcs(node, hdc_info);
	}
}

/*
 *	Given a shell, executes all its heredocs by browsing its associated AST
 *	If one of the subshells were interrupted by a signal, the shell's
 *	heredoc_interrupted flag is set to true
 *	Returns true on SUCCESS, false on ERROR (if an error occures during the
 *	heredoc executions
 */
bool	exec_ast_heredocs(t_minishell *shell)
{
	t_heredoc_exec_info	hdc_info;

	if (shell == NULL || shell->ast == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	hdc_info.interruption = false;
	hdc_info.error_flag = false;
	exec_ast_hdcs_process(shell->ast, &hdc_info);
	if (hdc_info.error_flag)
		return (false);
	if (hdc_info.interruption)
		shell->heredoc_interruption = true;
	return (true);
}
