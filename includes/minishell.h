/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:17:54 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/27 13:35:14 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define ERROR_MSG_PROMPT "Error - Prompt function error"

typedef struct s_minishell
{
	char	*input;
}	t_minishell;

// Prompt functions
char	*prompt(void);

// t_minshell functions
void	t_minishell_init(t_minishell *shell);
void	t_minishell_free(t_minishell *shell);

// General functions
void	handle_error(t_minishell *shell, char *error_msg, int exit_status);

#endif
