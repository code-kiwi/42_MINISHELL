/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:52:55 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/15 03:21:03 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

// General execution
void	exec_node(t_minishell *shell, t_node *node, int fd[2], bool in_pipe);

// Pipe execution
void	exec_node_pipe(t_minishell *shell, t_node *node, int fd[2]);

// Logical execution
void	exec_node_and(t_minishell *shell, t_node *node, int fd[2]);
void	exec_node_or(t_minishell *shell, t_node *node, int fd[2]);

// Command execution
char	*exec_cmd_get_path(t_minishell *shell, char *cmd);
void	exec_node_command(t_minishell *sh, t_node *n, int fd[2], bool in_pipe);
void	exec_cmd(t_minishell *shell, t_node_command *cmd);

// Builtin execution
int		exec_builtin(t_minishell *shell, t_node_command *cmd);

// Redirection execution
void	exec_redirection_list(t_redirection_list *redirection_list);
void	exec_redirection_heredoc(t_redirection *r, t_redirections_info *info);
void	exec_redirection_infile(t_redirection *red, \
			t_redirections_info *info, bool after_last_hd);
void	exec_redirection_out(t_redirection *red, t_redirections_info *info);

#endif
