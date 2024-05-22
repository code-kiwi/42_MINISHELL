/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:52:55 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/17 10:40:12 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdbool.h>

typedef struct s_minishell			t_minishell;
typedef struct s_node				t_node;
typedef struct s_node_command		t_node_command;
typedef struct s_redirection		t_redirection;
typedef struct s_redirection_list	t_redirection_list;
typedef struct s_redirections_info	t_redirections_info;

typedef struct s_heredoc_exec_info
{
	bool	interruption;
	bool	error_flag;
}	t_heredoc_exec_info;

// General execution
void	exec_ast(t_minishell *shell, int fds_given[2]);
void	exec_node(t_minishell *shell, t_node *node, int fd[2], bool in_pipe);

// Pipe execution
void	exec_node_pipe(t_minishell *shell, t_node *node, int fd[2]);

// Logical execution
void	exec_node_logical(t_minishell *shell, t_node *node, int fd[2]);

// Subshell execution
void	exec_node_subshell(t_minishell *shell, t_node *node, int fds[2]);

// Command execution
char	*exec_cmd_get_path(t_minishell *shell, char *cmd, int *status);
void	exec_node_command(t_minishell *sh, t_node *n, int fd[2], bool in_pipe);
void	exec_cmd(t_minishell *shell, t_node_command *cmd);

// Builtin execution
int		exec_builtin(t_minishell *shell, t_node_command *cmd);

// Redirection execution
void	exec_redirection_list(t_minishell *shell, \
			t_redirection_list *redirection_list);

// Heredoc execution
bool	exec_ast_heredocs(t_minishell *shell);
void	exec_redirection_list_heredocs(t_minishell *shell, \
			t_redirection_list *redirection_list, \
			t_heredoc_exec_info *hdc_info);
void	hdc_info_set_error(t_heredoc_exec_info *hdc_info);
void	hdc_info_set_interruption(t_heredoc_exec_info *hdc_info);
void	exec_expand_heredoc(t_minishell *shell, t_redirection_list *redir_list);

#endif
