/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:17:54 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/29 19:37:04 by brappo           ###   ########.fr       */
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
# define ERROR_CWD "Error - Cannot get current working directory path"
# define ERROR_BUFFER "Error - Buffer size too small"
# define CWD_BUFFER_SIZE 2048
# define RESET "\033[0m"
# define GREEN "\033[32m"
# define BLUE "\033[34m"

typedef struct s_minishell
{
	char	*input;
}	t_minishell;

// Prompt functions
void	get_directory_path(char *buffer, t_minishell *shell,
			size_t buffer_size);
char	*prompt(t_minishell *shell);

// t_minshell functions
void	t_minishell_init(t_minishell *shell);
void	t_minishell_free(t_minishell *shell);

// General functions
void	handle_error(t_minishell *shell, char *error_msg, int exit_status);

#endif
