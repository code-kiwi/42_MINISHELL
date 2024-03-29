/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:17:54 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/29 11:13:42 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "node.h"

# define ERROR_MSG_PROMPT	"Prompt function error"
# define ERROR_MSG_CLOSE	"Closing fd error"
# define DGREAT ">>"
# define DLESS "<<"
# define GREAT ">"
# define LESS "<"
# define AND_IF "||"
# define OR_IF "&&"
# define OPERATOR_CHARACTER "><&|"
# define OPERATOR_NUMBER 7

# define FD_UNSET -2

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
	char	*input;
	size_t	start;
	size_t	*end;
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
void	fd_close_and_reset(int *fd);
void	fd_close(int fd);

// Token recognition functions
int		is_operator(t_token_parser *token_parser);
bool	is_quoted(t_token_parser *token_parser);
void	t_token_parser_init(t_token_parser *token_parser,
			size_t *index, char *input);
t_token	*t_token_init(void);
bool	is_blank(char character);
void	t_token_free(void *token_void);
t_list	*token_recognition(char *input);
void	print_list_token(t_list *lst);
bool	handle_quote(t_token_parser *token_parser, char character);
int		array_find(void **array, bool (equal)(void *a, void *b), void *value);
bool	is_prefix(void	*word, void *prefix);
bool	is_operator_character(char character);
t_list	*lst_push_front_content(t_list **head, void *content);
#endif
