/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:28:12 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/12 11:16:05 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdlib.h>
# include <stdbool.h>

# define SHELL_EOF	"Unexpected end of file"

typedef struct s_minishell	t_minishell;
typedef struct s_list		t_list;

typedef enum e_token_type
{
	END,
	WORD,
	OPERATOR,
	OPERATOR_DGREAT,
	OPERATOR_DLESS,
	OPERATOR_GREAT,
	OPERATOR_LESS,
	OPERATOR_AND_IF,
	OPERATOR_OR_IF,
	OPERATOR_PIPE,
	OPERATOR_SHELL_OPEN,
	OPERATOR_SHELL_CLOSE,
	ASSIGNEMENT_WORD
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
t_token	*t_token_init(char *str, t_token_type type);
bool	is_blank(char character);
void	t_token_free(void *token_void);
t_list	*tokenize_str(char *str, t_token_parser *token_parser);
bool	handle_quote(t_token_parser *token_parser, char character);
int		array_find(void **array, bool (equal)(void *a, void *b), void *value);
bool	is_prefix(void	*word, void *prefix);
bool	is_operator_character(char character);
t_list	*lst_push_front_content(t_list **head,
			void *content, void free_content(void *));
char	*join_into_dest(char **dest, char *str);
void	get_operation(char **operations);
bool	add_token(t_list **head, char *str, t_token_type type);
t_list	*get_end_token_list(void);

//multi line input
bool	append_token_list(bool is_first_quoted, t_list **first, t_list *second);
void	print_token(void *token_void);
void	token_recognition(t_minishell *shell);

#endif
