/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:44:49 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/24 16:31:40 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"

# define NB_BUILT_IN 8

# define STATUS_EXIT_BAD_ARG	2
# define EXIT_MSG_BASIC			"exit"
# define EXIT_MSG_LITERAL		"%s\n"
# define EXIT_MSG_ARG_NON_NUM	"Error: exit: %s: numeric argument required\n"
# define EXIT_MSG_TOO_MANY_ARGS	"Error: exit: too many arguments"
# define ECHO_MSG_LITERAL		"Error: echo: %s\n"

typedef int	(*t_bi_func)(t_minishell *shell, char **argv);

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
int			bi_echo(t_minishell *shell, char **argv);
int			bi_cd(t_minishell *shell, char **argv);
int			bi_pwd(t_minishell *shell, char **argv);
int			bi_export(t_minishell *shell, char **argv);
int			bi_unset(t_minishell *shell, char **argv);
int			bi_env(t_minishell *shell, char **argv);
int			bi_exit(t_minishell *shell, char **argv);
int			bi_which(t_minishell *shell, char **argv);

#endif
