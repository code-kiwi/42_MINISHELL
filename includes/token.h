/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:28:12 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/05 11:24:16 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

# define MULTIPLE_LINE_PROMPT "> "

typedef struct s_minishell	t_minishell;

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

// Token recognition functions
int		is_operator(t_token_parser *token_parser);
bool	is_quoted(t_token_parser *token_parser);
void	t_token_parser_init(t_token_parser *token_parser);
t_token	*t_token_init(void);
bool	is_blank(char character);
void	t_token_free(void *token_void);
t_list	*tokenize_str(char *str, t_token_parser *token_parser);
bool	handle_quote(t_token_parser *token_parser, char character);
int		array_find(void **array, bool (equal)(void *a, void *b), void *value);
bool	is_prefix(void	*word, void *prefix);
bool	is_operator_character(char character);
t_list	*lst_push_front_content(t_list **head, void *content);
char	*join_into_dest(char **dest, char *str);

//multi line input
bool	append_token_list(bool is_first_quoted, t_list *first, t_list *second);
void	print_token(void *token_void);
void	token_recognition(t_minishell *shell);
void	token_error(t_minishell *shell);

//variable expansion
void	get_variable_key_coordinates(char *input, ssize_t *coordinates,
			size_t variable_start);
bool	expand_string(char **input);
#endif