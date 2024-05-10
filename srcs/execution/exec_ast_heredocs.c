/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_heredocs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:54:05 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/10 16:57:16 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "minishell.h"
#include "node.h"
#include "execution.h"

/*
 *	Given a node, returns its redirection list
 *	In case of ERROR, returns NULL (invalid arg. or invalide node type)
 *	NB: the only accepted nodes are NODE_COMMAND and NODE_SUBSHELL
 */
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

/*
 *	Given a node, executes its redirection's heredocs
 *	The heredoc execution information (error or interruption) will be set into
 *	the givenhdc_info
 *	In case of ERROR, sets hdc_info's error member to true and returns
 */
static void	exec_node_hdcs(
	t_minishell *shell, t_node *node, t_heredoc_exec_info *hdc_info
)
{
	t_redirection_list	*redirs;

	if (
		hdc_info == NULL || hdc_info->error_flag || node == NULL
		|| node->content == NULL
	)
		return (hdc_info_set_error(hdc_info));
	if (hdc_info->interruption)
		return ;
	redirs = get_node_redirs(node);
	if (redirs == NULL)
		return (hdc_info_set_error(hdc_info));
	exec_redirection_list_heredocs(shell, redirs, hdc_info);
}

/*
 *	Given a node and heredoc_info, browses the AST binary tree (Depth First Sch)
 *	and executes each node's heredoc redirections
 *	If the node is a SUBSHELL one:
 *		- executes the heredocs of the subshell's AST member
 *		- executes the subshell node's heredocs
 *	NB: This function is recursive, it stops if hdc_info requires it, if the
 *	given node is NULL or if hdc_info is invalid
 */
static void	exec_ast_hdcs_process(
	t_minishell *shell, t_node *node, t_heredoc_exec_info *hdc_info
)
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
		exec_ast_hdcs_process(shell, node->child_left, hdc_info);
		exec_ast_hdcs_process(shell, node->child_right, hdc_info);
	}
	else if (node->type == NODE_COMMAND)
		exec_node_hdcs(shell, node, hdc_info);
	else if (node->type == NODE_SUBSHELL)
	{
		node_sub = (t_node_subshell *) node->content;
		exec_ast_hdcs_process(shell, node_sub->ast, hdc_info);
		exec_node_hdcs(shell, node, hdc_info);
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
	exec_ast_hdcs_process(shell, shell->ast, &hdc_info);
	if (hdc_info.error_flag)
		return (false);
	if (hdc_info.interruption)
		shell->heredoc_interruption = true;
	return (true);
}
