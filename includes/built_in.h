/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:44:49 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/26 17:46:00 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include <stdbool.h>

# define NB_BUILT_IN			7
# define STATUS_EXIT_BAD_ARG	2
# define MSG_LITERAL			"%s\n"

# define EXIT_MSG_BASIC			"exit"
# define EXIT_MSG_ARG_NON_NUM	"Error: exit: %s: numeric argument required\n"
# define EXIT_MSG_TOO_MANY_ARGS	"Error: exit: too many arguments"

# define ECHO_MSG_LITERAL		"Error: echo: %s\n"

# define PWD_MSG_ERROR			"Error: pwd failed"

# define CD_MSG_LITERAL1		"Error: cd: %s\n"
# define CD_MSG_LITERAL2		"Error: cd: %s: %s\n"
# define CD_MSG_ERR_INTERNAL	"Internal process error"
# define CD_MSG_ERR_HOME		"HOME not set"
# define CD_MSG_ERR_ARGS		"Too many arguments"
# define CD_MSG_ERR_EXISTS		"No such file or directory"

# define ENV_MSG_ERR_ARG		"Error: env: No argument expected\n"
# define ENV_MSG_ERR_INTERNAL	"Error: env: Internal error occured\n"

typedef struct s_minishell	t_minishell;
typedef int					(*t_bi_func)(t_minishell *sh, char **av, int fdout);

typedef struct s_bi_component
{
	char		*name;
	t_bi_func	func;
}	t_bi_component;

// Utils functions
bool		is_built_in(t_bi_component bi_funcs[NB_BUILT_IN], char *cmd_name);
t_bi_func	built_in_get(t_bi_component bi_funcs[NB_BUILT_IN], char *cmd_name);
void		built_in_init_array(t_bi_component bi_funcs[NB_BUILT_IN]);

// Built-in functions
int			bi_echo(t_minishell *shell, char **argv, int fd_out);
int			bi_cd(t_minishell *shell, char **argv, int fd_out);
int			bi_cd_handle_error(char *msg, int status, char *dir);
int			bi_cd_execution(t_minishell *shell, char *path);
int			bi_pwd(t_minishell *shell, char **argv, int fd_out);
int			bi_export(t_minishell *shell, char **argv, int fd_out);
int			bi_unset(t_minishell *shell, char **argv, int fd_out);
int			bi_env(t_minishell *shell, char **argv, int fd_out);
int			bi_exit(t_minishell *shell, char **argv, int fd_out);

#endif
