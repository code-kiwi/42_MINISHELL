/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:17:54 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/28 09:34:15 by brappo           ###   ########.fr       */
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

typedef enum e_token_type
{
	END,
	WORD,
	OPERATOR
}	t_token_type;

typedef struct s_token_parser
{
	bool	single_quoted;
	bool	double_quoted;
}	t_token_parser;

typedef struct s_token
{
	char			*str;
	size_t			length;
	t_token_type	type;	
}	t_token;

// Prompt functions
char	*prompt(void);

// t_minshell functions
void	t_minishell_init(t_minishell *shell);
void	t_minishell_free(t_minishell *shell);

// General functions
void	handle_error(t_minishell *shell, char *error_msg, int exit_status);

// Token recognition functions
bool	is_operator(char character);
bool	is_quoted(t_token_parser *token_parser);
void	t_token_parser_init(t_token_parser *token_parser);
t_token	*t_token_init(void);
bool	is_blank(char character);
void	t_token_free(void *token_void);
t_list	*token_recognition(char *input);
void	print_list(t_list *lst);
#endif
