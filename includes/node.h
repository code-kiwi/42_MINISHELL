/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:53:48 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/29 10:30:48 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

# include "redirections.h"

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
	t_redirection_list		*redirection_list;
}	t_node_command;

// t_node functions
t_node	*node_create_empty(t_node_type type);
void	node_free_single(t_node **node_ptr);
void	ast_free(t_node **node_ptr);

// t_node_command functions
t_node	*node_command_create(int argc, char **argv);
void	node_command_free(void **node_ptr);
bool	node_command_add_redirection(t_node *node, char *op, char *filename);

// t_node_pipe_functions
t_node	*node_pipe_create(void);
void	node_pipe_free(void **node_ptr);

#endif
