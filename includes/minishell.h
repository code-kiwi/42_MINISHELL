/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:17:54 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/04 10:37:26 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "prompt.h"
# include "libft.h"
# include "node.h"
# include "token.h"
# include "env.h"

# define ERROR_MSG_CLOSE	"Closing fd error"
# define DGREAT 			">>"
# define DLESS				"<<"
# define GREAT				">"
# define LESS				"<"
# define AND_IF				"||"
# define OR_IF				"&&"
# define OPERATOR_CHARACTER	"><&|"
# define OPERATOR_NUMBER 	7

# define FD_UNSET			-2

typedef struct s_minishell
{
	char	*input;
	t_list	*env;
}	t_minishell;

// t_minshell functions
void	t_minishell_init(t_minishell *shell, int ac, char **av, char **envp);
void	t_minishell_free(t_minishell *shell);

// General functions
void	handle_error(t_minishell *shell, char *error_msg, int exit_status);
void	fd_close_and_reset(int *fd);
void	fd_close(int fd);
char	**ft_split_key_val(char *str, char sep);

#endif
