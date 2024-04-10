/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:17:54 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/10 16:42:50 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

# define ERROR_MSG_CLOSE	"Closing fd error"
# define ERROR_MSG_FORK		"Impossible to fork"
# define ERROR_MSG_MEM		"Memory allocation problem"
# define TOKENIZATION_ERROR "Tokenizing input"

# define DGREAT 			">>"
# define DLESS				"<<"
# define GREAT				">"
# define LESS				"<"
# define OR_IF				"||"
# define AND_IF				"&&"
# define PIPE				"|"
# define OPERATOR_CHARACTER	"><&|"
# define OPERATOR_NUMBER 	7

# define FD_UNSET			-2
# define FD_ERROR			-1

# define PID_ERROR			0

typedef struct s_minishell
{
	char				*input;
	t_list				*env;
	t_list				*tokens;
	struct s_pid_list	*pid_list;
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
