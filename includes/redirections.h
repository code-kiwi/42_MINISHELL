/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:06:44 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/29 10:30:35 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "minishell.h"

# define REDIRECTION_OP_HEREDOC			"<<"
# define REDIRECTION_OP_INFILE			"<"
# define REDIRECTION_OP_OUTFILE_TRUNC	">"
# define REDIRECTION_OP_OUTFILE_APPEND	">>"

enum e_redirection_type
{
	REDIRECTION_TYPE_ERROR = 0,
	REDIRECTION_TYPE_HEREDOC,
	REDIRECTION_TYPE_INFILE,
	REDIRECTION_TYPE_OUTFILE_TRUNC,
	REDIRECTION_TYPE_OUTFILE_APPEND,
};

typedef struct s_redirections_info
{
	int		fd_stdin;
	int		fd_stdout;
	bool	error_infile;
	bool	error_outfile;
}	t_redirections_info;

typedef struct s_redirection_list
{
	t_redirections_info	info;
	t_list				*redirections;
}	t_redirection_list;

typedef struct s_redirection
{
	enum e_redirection_type	type;
	char					*filename;
}	t_redirection;

// t_redirections functions
t_redirection_list	*redirection_list_create(void);
bool				redirection_list_add(t_redirection_list *redirs, \
					char *op, char *filename);
void				redirection_list_free(t_redirection_list **redirs_ptr);

// t_redirection functions
t_redirection		*redirection_create(char *op, char *filename);
void				redirection_free(void *redirection_ptr);

#endif