/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:52:55 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/12 15:42:16 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

// Command execution
void	exec_cmd_handler(t_minishell *sh, t_node *node, \
			int fin, int fout, bool in_pipe);
void	exec_cmd(t_minishell *shell, t_node_command *cmd);

// Builtin execution
int		exec_builtin(t_minishell *shell, t_node_command *cmd);

// Redirection execution
void	exec_redirection_list(t_redirection_list *redirection_list);
void	exec_redirection_heredoc(t_redirection *red, t_redirections_info *info);
void	exec_redirection_infile(t_redirection *red, \
			t_redirections_info *info, bool after_last_hd);
void	exec_redirection_out(t_redirection *red, t_redirections_info *info);

#endif
