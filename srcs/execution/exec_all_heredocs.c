/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_heredocs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:54:05 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/03 11:22:11 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "minishell.h"
#include "node.h"

typedef struct s_heredoc_exec_info
{
	bool	interruption;
	bool	error_flag;
}	t_heredoc_exec_info;

static void	exec_ast_hdcs_process(t_node *node, t_heredoc_exec_info *hdc_info);

static void	exec_node_subshell_hdcs(t_node *node, t_heredoc_exec_info *hdc_info)
{
	t_node_subshell	*node_sub;

	if (node == NULL || node->content == NULL || node->type != NODE_SUBSHELL)
		return ;
	node_sub = (t_node_subshell *) node->content;
	if (!node_subshell_build_ast(node))
	{
		hdc_info->error_flag = true;
		return ;
	}
	node_sub = (t_node_subshell *) node->content;
	exec_ast_heredocs_process(node_sub->ast, hdc_info);
	exec_node_heredocs(node, hdc_info);
}

static void	exec_ast_hdcs_process(t_node *node, t_heredoc_exec_info *hdc_info)
{
	if (node == NULL || hdc_info == NULL || hdc_info->error_flag || hdc_info->interruption)
		return ;
	if (node->type == NODE_PIPE || node->type == NODE_AND || node->type == NODE_OR)
	{
		exec_ast_hdcs_process(node->child_left, hdc_info);
		exec_ast_hdcs_process(node->child_right, hdc_info);
	}
	else if (node->type == NODE_COMMAND)
		exec_node_hdcs(node, hdc_info);
	else if (node->type == NODE_SUBSHELL)
		exec_node_subshell_hdcs(node, hdc_info);
}

bool	exec_ast_heredocs(t_minishell *shell)
{
	t_heredoc_exec_info	hdc_info;

	if (shell == NULL || shell->ast == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	hdc_info.interruption = false;
	hdc_info.error_flag = false;
	exec_ast_heredocs_process(shell->ast, &hdc_info);
	if (hdc_info.error_flag)
		return (false);
	if (hdc_info.interruption)
		shell->heredoc_interruption = true;
	return (true);
}
