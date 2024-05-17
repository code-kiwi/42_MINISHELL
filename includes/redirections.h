/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:06:44 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/17 12:32:03 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include <stdlib.h>
# include <stdbool.h>
# include <sys/types.h>

# define ERROR_HERE_DOC_EOF \
	"Warning: Here-document delimited by end of file (wanted \"%s\")\n"

typedef struct s_list	t_list;

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
	ssize_t	hdc_last_pos;
	bool	fdin_is_heredoc;
	bool	hdc_needs_expansion;
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

// t_redirection_list functions
t_redirection_list	*redirection_list_create(void);
bool				redirection_list_add(t_redirection_list *redirs, \
					char *op, char *filename);
void				redirection_list_free(t_redirection_list **redirs_ptr);
bool				redirection_list_has_error(t_redirection_list *redir_list);

// t_redirection functions
t_redirection		*redirection_create(char *op, char *filename);
void				redirection_free(void *redirection_ptr);

#endif
