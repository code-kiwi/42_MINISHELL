/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:17:54 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/14 12:59:16 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>

# include "prompt.h"
# include "libft.h"
# include "node.h"
# include "token.h"
# include "env.h"
# include "execution.h"
# include "pid_list.h"
# include "built_in.h"

# define STATUS_CMD_NOT_FOUND	127
# define STATUS_CMD_NOT_EXEC	126
# define ERROR_MSG_ARGS			"Wrong arguments given to the function"
# define ERROR_MSG_CLOSE		"Closing fd error"
# define ERROR_MSG_FORK			"Impossible to fork"
# define ERROR_MSG_MEM			"Memory allocation problem"
# define ERROR_MSG_PIPE			"Impossible to pipe"
# define ERROR_MSG_HEREDOC		"Impossible to read here_doc"
# define ERROR_MSG_SUBSTITUTION "Invalid variable substitution"
# define ERROR_MSG_CMD_NOTFOUND	"Command not found"
# define ERROR_MSG_CMD_REDIR	"File descriptor redirection impossible"
# define ERROR_MSG_CMD_EXEC		"Command execution impossible"
# define TOKENIZATION_ERROR 	"Tokenizing input"

# define DGREAT 				">>"
# define DLESS					"<<"
# define GREAT					">"
# define LESS					"<"
# define OR_IF					"||"
# define AND_IF					"&&"
# define PIPE					"|"
# define OPERATOR_CHARACTER		"><&|"
# define OPERATOR_NUMBER 		7
# define PATH_STR_SEPERATOR		":"

# define FD_UNSET				-2
# define FD_ERROR				-1

# define PID_ERROR				0

# define MULTIPLE_LINE_PROMPT	"> "

typedef struct s_minishell
{
	char				*input;
	t_list				*env;
	t_list				*tokens;
	struct s_pid_list	*pid_list;
	bool				is_child_process;
	t_node				*ast;
}	t_minishell;

// t_minshell functions
void	t_minishell_init(t_minishell *shell, int ac, char **av, char **envp);
void	t_minishell_free(t_minishell *shell);
bool	t_minishell_add_pid(t_minishell *shell, pid_t pid);
int		t_minishell_wait_pids(t_minishell *shell);

// General functions
void	handle_error(t_minishell *shell, char *error_msg, int exit_status);
void	fd_close_and_reset(int *fd);
void	fd_close(int fd);
char	**ft_split_key_val(char *str, char sep);
char	*bridge(char *first, char *second, char *separator);
char	*bridge_into_first(char **first, char *second, char *separator);
void	ft_print_str_array(char **array);
#endif
