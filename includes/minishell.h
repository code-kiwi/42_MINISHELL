/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:17:54 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/17 11:37:19 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdlib.h>
# include <sys/types.h>
# include "built_in.h"

typedef struct s_list			t_list;
typedef struct s_node			t_node;
typedef struct s_minishell		t_minishell;

# define STATUS_INVALID_USE		2
# define STATUS_CMD_NOT_FOUND	127
# define STATUS_CMD_NOT_EXEC	126
# define STATUS_SIGINT_STOP		130
# define ERROR_MSG_ARGS			"Wrong arguments given to the function"
# define ERROR_MSG_CLOSE		"Closing fd error"
# define ERROR_MSG_FORK			"Impossible to fork"
# define ERROR_MSG_MEM			"Memory allocation problem"
# define ERROR_MSG_PIPE			"Impossible to open a pipe"
# define ERROR_MSG_HEREDOC		"Impossible to read here_doc"
# define ERROR_MSG_HEREDOC_EXEC	"Execution of the here_docs failed"
# define ERROR_MSG_HEREDOC_EXP	"Expansion of the here_docs failed"
# define ERROR_MSG_SUBSTITUTION "Invalid variable substitution"
# define ERROR_MSG_CMD_NFND		"Command not found"
# define ERROR_MSG_CMD_REDIR	"File descriptor redirection impossible"
# define ERROR_MSG_CMD_EXEC		"Command execution impossible"
# define ERROR_MSG_CMD_PRM		"Permission denied"
# define ERROR_MSG_CMD_DIR		"Is a directory"
# define ERROR_MSG_DUP			"Impossible to duplicate a file descriptor"
# define ERROR_MSG_SHELL_CPY	"Impossible to create a subshell"
# define ERROR_MSG_AST_CREATION	"AST creation failed"
# define ERROR_MSG_SUBAST		"Subshell AST creation failed"
# define ERROR_MSG_WRONG_BI		"The built-in does not exist"
# define ERROR_MSG_WRITE		"Call to write function failed"
# define ERROR_MSG_TOKENIZATION	"Tokenizing input"
# define ERROR_MSG_PROMPT		"Prompt function error"
# define ERROR_MSG_ENV_CREATION	"Impossible to initialize the environment"
# define ERROR_MSG_EXPANSION	"Expansion failed"
# define ERROR_MSG_AMBIG_REDIR	"Ambiguous redirection"
# define ERROR_MSG_BUILD_AST	"Syntax error near unexpected token"
# define ERROR_MSG_NOTATTY		"Not a tty: STDIN redirection not handled"
# define ERROR_MSG_SIGNAL_INIT	"Signal handling set up failed"
# define ERROR_MSG_BAD_CHARS	"The input must contain only ASCII chars"
# define ERROR_MSG_BAD_OPERATOR	"Minishell: Unknown operator"
# define ERROR_MSG_ERRNO		"The errno value is not 0 at loop end"
# define ERROR_TEMPL			"Minishell: %s: %s\n"

# define DGREAT 				">>"
# define DLESS					"<<"
# define GREAT					">"
# define LESS					"<"
# define OR_IF					"||"
# define AND_IF					"&&"
# define PIPE					"|"
# define SHELL_OPEN				"("
# define SHELL_CLOSE			")"
# define OPERATOR_CHARACTER		"><&|()"
# define OPERATOR_NUMBER		9
# define PATH_STR_SEPERATOR		":"

# define FD_UNSET				-2
# define FD_ERROR				-1
# define PID_ERROR				0

# define MULTIPLE_LINE_PROMPT	"> "
# define HEREDOC_PROMPT			"heredoc> "

# define ENV_PWD				"PWD"
# define ENV_OLDPWD				"OLDPWD"
# define ENV_PATH				"PATH"
# define ENV_SHLVL				"SHLVL"
# define ENV_TERM				"TERM"
# define ENV_HOME				"HOME"
# define ENV_USER				"USER"
# define ENV_UNDERSCORE			"_"
# define ENV_DEFAULT_UNDERSCORE	"/usr/bin/env"

# define CMD_EXPORT				"export"

struct s_minishell
{
	char				*input;
	t_list				*env;
	t_list				*tokens;
	struct s_pid_list	*pid_list;
	bool				is_child_process;
	t_node				*ast;
	int					status;
	t_minishell			*parent;
	t_bi_component		bi_funcs[NB_BUILT_IN];
	bool				heredoc_interruption;
	bool				is_a_tty;
};

// t_minshell functions
void	t_minishell_init(t_minishell *shell, int ac, char **av, char **envp);
void	t_minishell_free(t_minishell *shell);
bool	t_minishell_add_pid(t_minishell *shell, pid_t pid);
bool	t_minishell_set_exec_status(t_minishell *shell);
void	t_minishell_init_subshell(t_minishell *sub, t_minishell *parent);
void	utils_reset_shell(t_minishell *shell, int status);
t_list	*t_minishell_env_init(char **envp);

// General functions
void	handle_error(t_minishell *shell, char *error_msg, int exit_status);
void	handle_error_cmd(t_minishell *shell, char *err_msg, char *cmd);
void	fd_close_and_reset(int *fd);
void	fd_close(int fd);
bool	is_fd_ok(int fd);
void	fds_init(int fds[2]);
void	fds_close_and_reset(int fds[2]);
char	**ft_split_key_val(char *str, char *key);
char	*bridge(char *first, char *second, char *separator);
char	*bridge_into_first(char **first, char *second, char *separator);
bool	string_equals(void *a, void *b);
bool	string_contains_only_spaces(char *str);
bool	string_contains_invalid_chars(char *str);
void	**to_array(t_list *lst);
bool	utils_is_empty_cmd(char *cmd);
size_t	array_size(void **array);
bool	path_is_dir(char *path);

#endif
