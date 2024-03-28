/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:53:48 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/28 09:51:27 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

# define NUM_NODE_TYPE 2

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
}	t_node_type;

typedef struct s_node
{
	t_node_type		type;
	void			*content;
	struct s_node	*child_left;
	struct s_node	*child_right;
}	t_node;

typedef struct s_node_pipe
{
	int	fd[2];
	int	received_stdin;
}	t_node_pipe;

typedef struct s_node_command
{
	int						argc;
	char					**argv;
	struct s_redirection	*redirections;
}	t_node_command;

typedef struct s_redirection
{
	char	*here_doc;
	char	*infile;
	char	*outfile_append;
	char	*outfile_truncate;
}	t_redirection;

// t_node functions
t_node			*create_pipe_node(void);
t_node			*create_command_node(int argc, char **argv, t_redirection *red);
void			free_node_content_command(void **node_ptr);
void			free_node_content_pipe(void **node_ptr);
void			free_ast(t_node **node_ptr);

// t_redirection functions
t_redirection	*create_redirection(char *here_doc, \
			char *infile, char *outfile_append, char *outfile_truncate);
void			free_redirection(t_redirection **redirection_ptr);

#endif
