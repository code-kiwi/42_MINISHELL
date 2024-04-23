/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execution2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:51:24 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/23 21:01:40 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_print_redirection(void *red);
void	test_print_redirection_list(t_redirection_list *red);
t_node	*node_cmd_create(char *cmd);
bool	node_cmd_add_redirs(t_node *node, char *op, char *filename);
void	node_cmd_print(t_node *node);
t_node	*node_pip_create(t_node *left, t_node *right);
t_node	*node_and_create_test(t_node *left, t_node *right);
t_node	*node_or_create_test(t_node *left, t_node *right);
void	t_minishell_print(t_minishell *shell);
bool	node_sub_add_redirs(t_node *node, char *op, char *filename);
t_node	*node_subshell_create_test(void);

/* ********************************************************************** */
// AST_CREATION

/*
 *	Returns an AST for the command: "< Makefile cat | cat | cat > outfile"
 */
static t_node	*ast_create1(void)
{
	t_node	*node_c1;
	t_node	*node_c2;
	t_node	*node_c3;
	t_node	*node_pipe1;
	t_node	*node_pipe2;

	// Creates node_c1
	node_c1 = node_cmd_create("cat");
	if (node_c1 == NULL)
		return (NULL);
	if (!node_cmd_add_redirs(node_c1, "<", "Makefile"))
		return (NULL);
	
	// Creates node_c2
	node_c2 = node_cmd_create("cat");
	if (node_c2 == NULL)
		return (NULL);

	// Creates node_c3
	node_c3 = node_cmd_create("cat");
	if (node_c3 == NULL)
		return (NULL);
	if (!node_cmd_add_redirs(node_c3, ">", "outfile"))
		return (NULL);

	// Creates pipe node
	node_pipe2 = node_pip_create(node_c2, node_c3);
	if (node_pipe2 == NULL)
		return (NULL);
	node_pipe1 = node_pip_create(node_c1, node_pipe2);
	if (node_pipe1 == NULL)
		return (NULL);
	return (node_pipe1);
}

/*
 *	Returns an AST for the command: "ls -la && sleep 5"
 */
static t_node	*ast_create2(void)
{
	t_node	*node_c1;
	t_node	*node_c2;
	t_node	*node_and;

	// Creates node_c1
	node_c1 = node_cmd_create("ls -la");
	if (node_c1 == NULL)
		return (NULL);
	
	// Creates node_c2
	node_c2 = node_cmd_create("sleep 5");
	if (node_c2 == NULL)
		return (NULL);

	// Creates and node
	node_and = node_and_create_test(node_c1, node_c2);
	if (node_and == NULL)
		return (NULL);
	return (node_and);
}

/*
 *	Returns an AST for the command: "echo 1 | cat && echo 2"
 */
static t_node	*ast_create3(void)
{
	t_node	*node_c1;
	t_node	*node_c2;
	t_node	*node_c3;
	t_node	*node_and;
	t_node	*node_pipe;

	// Creates node_c1
	node_c1 = node_cmd_create("echo 1");
	if (node_c1 == NULL)
		return (NULL);
	
	// Creates node_c2
	node_c2 = node_cmd_create("cat");
	if (node_c2 == NULL)
		return (NULL);

	// Creates node_c3
	node_c3 = node_cmd_create("ech 2");
	if (node_c3 == NULL)
		return (NULL);
	if (!node_cmd_add_redirs(node_c3, ">>", "outfile"))
		return (NULL);

	// Creates pipe node
	node_pipe = node_pip_create(node_c1, node_c2);
	if (node_pipe == NULL)
		return (NULL);

	// Creates and node
	node_and = node_and_create_test(node_pipe, node_c3);
	if (node_and == NULL)
		return (NULL);
	return (node_and);
}

/*
 *	Returns an AST for the command: "echo 42 | echo no | echo smth | grep no"
 */
static t_node	*ast_create4(void)
{
	t_node	*node_c1;
	t_node	*node_c2;
	t_node	*node_c3;
	t_node	*node_c4;
	t_node	*node_pipe1;
	t_node	*node_pipe2;
	t_node	*node_pipe3;

	// Creates node_c1
	node_c1 = node_cmd_create("echo 42");
	if (node_c1 == NULL)
		return (NULL);
	
	// Creates node_c2
	node_c2 = node_cmd_create("echo no");
	if (node_c2 == NULL)
		return (NULL);

	// Creates node_c3
	node_c3 = node_cmd_create("echo smth");
	if (node_c3 == NULL)
		return (NULL);

	// Creates node_c4
	node_c4 = node_cmd_create("grep no");
	if (node_c4 == NULL)
		return (NULL);

	// Creates pipe node
	node_pipe3 = node_pip_create(node_c3, node_c4);
	if (node_pipe3 == NULL)
		return (NULL);

	// Creates pipe node
	node_pipe2 = node_pip_create(node_c2, node_pipe3);
	if (node_pipe2 == NULL)
		return (NULL);

	// Creates pipe node
	node_pipe1 = node_pip_create(node_c1, node_pipe2);
	if (node_pipe1 == NULL)
		return (NULL);

	return (node_pipe1);
}

/*
 *	Returns an AST for the command: "echo 42 && echo no && echo smth && echo 36"
 */
static t_node	*ast_create5(void)
{
	t_node	*node_c1;
	t_node	*node_c2;
	t_node	*node_c3;
	t_node	*node_c4;
	t_node	*node_and1;
	t_node	*node_and2;
	t_node	*node_and3;

	// Creates node_c1
	node_c1 = node_cmd_create("echo 42");
	if (node_c1 == NULL)
		return (NULL);
	
	// Creates node_c2
	node_c2 = node_cmd_create("echo no");
	if (node_c2 == NULL)
		return (NULL);

	// Creates node_c3
	node_c3 = node_cmd_create("echo smth");
	if (node_c3 == NULL)
		return (NULL);

	// Creates node_c4
	node_c4 = node_cmd_create("echo 36");
	if (node_c4 == NULL)
		return (NULL);

	// Creates and node
	node_and3 = node_and_create_test(node_c1, node_c2);
	if (node_and3 == NULL)
		return (NULL);

	// Creates and node
	node_and2 = node_and_create_test(node_and3, node_c3);
	if (node_and2 == NULL)
		return (NULL);

	// Creates and node
	node_and1 = node_and_create_test(node_and2, node_c4);
	if (node_and1 == NULL)
		return (NULL);

	return (node_and1);
}

/*
 *	Returns an AST for the command: "echo 42 && echo no && ech smth && echo 36"
 */
static t_node	*ast_create6(void)
{
	t_node	*node_c1;
	t_node	*node_c2;
	t_node	*node_c3;
	t_node	*node_c4;
	t_node	*node_and1;
	t_node	*node_and2;
	t_node	*node_and3;

	// Creates node_c1
	node_c1 = node_cmd_create("echo 42");
	if (node_c1 == NULL)
		return (NULL);
	
	// Creates node_c2
	node_c2 = node_cmd_create("echo no");
	if (node_c2 == NULL)
		return (NULL);

	// Creates node_c3
	node_c3 = node_cmd_create("ech smth");
	if (node_c3 == NULL)
		return (NULL);

	// Creates node_c4
	node_c4 = node_cmd_create("echo 36");
	if (node_c4 == NULL)
		return (NULL);

	// Creates and node
	node_and3 = node_and_create_test(node_c1, node_c2);
	if (node_and3 == NULL)
		return (NULL);

	// Creates and node
	node_and2 = node_and_create_test(node_and3, node_c3);
	if (node_and2 == NULL)
		return (NULL);

	// Creates and node
	node_and1 = node_and_create_test(node_and2, node_c4);
	if (node_and1 == NULL)
		return (NULL);

	return (node_and1);
}

/*
 *	Returns an AST for the command: "echo 42 || echo no || echo smth || echo 36"
 */
static t_node	*ast_create7(void)
{
	t_node	*node_c1;
	t_node	*node_c2;
	t_node	*node_c3;
	t_node	*node_c4;
	t_node	*node_or1;
	t_node	*node_or2;
	t_node	*node_or3;

	// Creates node_c1
	node_c1 = node_cmd_create("echo 42");
	if (node_c1 == NULL)
		return (NULL);
	
	// Creates node_c2
	node_c2 = node_cmd_create("echo no");
	if (node_c2 == NULL)
		return (NULL);

	// Creates node_c3
	node_c3 = node_cmd_create("echo smth");
	if (node_c3 == NULL)
		return (NULL);

	// Creates node_c4
	node_c4 = node_cmd_create("echo 36");
	if (node_c4 == NULL)
		return (NULL);

	// Creates or node
	node_or3 = node_or_create_test(node_c1, node_c2);
	if (node_or3 == NULL)
		return (NULL);

	// Creates or node
	node_or2 = node_or_create_test(node_or3, node_c3);
	if (node_or2 == NULL)
		return (NULL);

	// Creates or node
	node_or1 = node_or_create_test(node_or2, node_c4);
	if (node_or1 == NULL)
		return (NULL);

	return (node_or1);
}

/*
 *	Returns an AST for the command: "ech 42 || ech no || ech smth || echo 36"
 */
static t_node	*ast_create8(void)
{
	t_node	*node_c1;
	t_node	*node_c2;
	t_node	*node_c3;
	t_node	*node_c4;
	t_node	*node_or1;
	t_node	*node_or2;
	t_node	*node_or3;

	// Creates node_c1
	node_c1 = node_cmd_create("ech 42");
	if (node_c1 == NULL)
		return (NULL);
	
	// Creates node_c2
	node_c2 = node_cmd_create("ech no");
	if (node_c2 == NULL)
		return (NULL);

	// Creates node_c3
	node_c3 = node_cmd_create("ech smth");
	if (node_c3 == NULL)
		return (NULL);

	// Creates node_c4
	node_c4 = node_cmd_create("echo 36");
	if (node_c4 == NULL)
		return (NULL);

	// Creates or node
	node_or3 = node_or_create_test(node_c1, node_c2);
	if (node_or3 == NULL)
		return (NULL);

	// Creates or node
	node_or2 = node_or_create_test(node_or3, node_c3);
	if (node_or2 == NULL)
		return (NULL);

	// Creates or node
	node_or1 = node_or_create_test(node_or2, node_c4);
	if (node_or1 == NULL)
		return (NULL);

	return (node_or1);
}

/*
 *	Returns an AST for the command: "ech 42 || ech no || echo smth && echo 36"
 */
static t_node	*ast_create9(void)
{
	t_node	*node_c1;
	t_node	*node_c2;
	t_node	*node_c3;
	t_node	*node_c4;
	t_node	*node_and1;
	t_node	*node_or2;
	t_node	*node_or3;

	// Creates node_c1
	node_c1 = node_cmd_create("ech 42");
	if (node_c1 == NULL)
		return (NULL);
	
	// Creates node_c2
	node_c2 = node_cmd_create("ech no");
	if (node_c2 == NULL)
		return (NULL);

	// Creates node_c3
	node_c3 = node_cmd_create("echo smth");
	if (node_c3 == NULL)
		return (NULL);

	// Creates node_c4
	node_c4 = node_cmd_create("echo 36");
	if (node_c4 == NULL)
		return (NULL);

	// Creates or node
	node_or3 = node_or_create_test(node_c1, node_c2);
	if (node_or3 == NULL)
		return (NULL);

	// Creates or node
	node_or2 = node_or_create_test(node_or3, node_c3);
	if (node_or2 == NULL)
		return (NULL);

	// Creates and node
	node_and1 = node_and_create_test(node_or2, node_c4);
	if (node_and1 == NULL)
		return (NULL);

	return (node_and1);
}

/*
 *	Returns an AST for the command: "echo 42 && echo no && echo smth || echo 36"
 */
static t_node	*ast_create10(void)
{
	t_node	*node_c1;
	t_node	*node_c2;
	t_node	*node_c3;
	t_node	*node_c4;
	t_node	*node_or1;
	t_node	*node_and2;
	t_node	*node_and3;

	// Creates node_c1
	node_c1 = node_cmd_create("echo 42");
	if (node_c1 == NULL)
		return (NULL);
	
	// Creates node_c2
	node_c2 = node_cmd_create("echo no");
	if (node_c2 == NULL)
		return (NULL);

	// Creates node_c3
	node_c3 = node_cmd_create("echo smth");
	if (node_c3 == NULL)
		return (NULL);

	// Creates node_c4
	node_c4 = node_cmd_create("echo 36");
	if (node_c4 == NULL)
		return (NULL);

	// Creates and node
	node_and3 = node_and_create_test(node_c1, node_c2);
	if (node_and3 == NULL)
		return (NULL);

	// Creates and node
	node_and2 = node_and_create_test(node_and3, node_c3);
	if (node_and2 == NULL)
		return (NULL);

	// Creates or node
	node_or1 = node_or_create_test(node_and2, node_c4);
	if (node_or1 == NULL)
		return (NULL);

	return (node_or1);
}

/*
 *	Returns an AST for the command: "echo 42 && ech no && echo smth || echo 36"
 */
static t_node	*ast_create11(void)
{
	t_node	*node_c1;
	t_node	*node_c2;
	t_node	*node_c3;
	t_node	*node_c4;
	t_node	*node_or1;
	t_node	*node_and2;
	t_node	*node_and3;

	// Creates node_c1
	node_c1 = node_cmd_create("echo 42");
	if (node_c1 == NULL)
		return (NULL);
	
	// Creates node_c2
	node_c2 = node_cmd_create("ech no");
	if (node_c2 == NULL)
		return (NULL);

	// Creates node_c3
	node_c3 = node_cmd_create("echo smth");
	if (node_c3 == NULL)
		return (NULL);

	// Creates node_c4
	node_c4 = node_cmd_create("echo 36");
	if (node_c4 == NULL)
		return (NULL);

	// Creates and node
	node_and3 = node_and_create_test(node_c1, node_c2);
	if (node_and3 == NULL)
		return (NULL);

	// Creates and node
	node_and2 = node_and_create_test(node_and3, node_c3);
	if (node_and2 == NULL)
		return (NULL);

	// Creates or node
	node_or1 = node_or_create_test(node_and2, node_c4);
	if (node_or1 == NULL)
		return (NULL);

	return (node_or1);
}


/*
 *	Returns an AST for the command: "(echo 1 | cat && echo 2)"
 *	NB: USES DUMMY node_sub CREATION!!!
 */
static t_node	*ast_create12(void)
{
	t_node	*node_sub;

	// Creates node_sub
	node_sub = node_subshell_create_test();
	if (node_sub == NULL)
		return (NULL);

	return (node_sub);
}

/*
 *	Returns an AST for the command: "(echo 1 | cat && echo 2) | cat"
 *	NB: USES DUMMY node_sub CREATION!!!
 */
static t_node	*ast_create13(void)
{
	t_node	*node_sub;
	t_node	*node_c2;
	t_node	*node_pipe;

	// Creates node_sub
	node_sub = node_subshell_create_test();
	if (node_sub == NULL)
		return (NULL);
	if (!node_sub_add_redirs(node_sub, ">>", "outfile1"))
		return (NULL);

	// Creates node_c2
	node_c2 = node_cmd_create("cat");
	if (node_c2 == NULL)
		return (NULL);

	// Creates pipe node
	node_pipe = node_pip_create(node_sub, node_c2);
	if (node_pipe == NULL)
		return (NULL);

	return (node_pipe);
}

/*
 *	Returns an AST for the command: "echo 12 | cat | (cat > outfile | echo 13)"
 *	NB: USES DUMMY node_sub CREATION!!!
 */
static t_node	*ast_create14(void)
{
	t_node	*node_c1;
	t_node	*node_c2;
	t_node	*node_sub;
	t_node	*node_pipe1;
	t_node	*node_pipe2;

	// Creates node_sub
	node_sub = node_subshell_create_test();
	if (node_sub == NULL)
		return (NULL);

	// Creates node_c1
	node_c1 = node_cmd_create("echo 12");
	if (node_c1 == NULL)
		return (NULL);

	// Creates node_c2
	node_c2 = node_cmd_create("cat");
	if (node_c2 == NULL)
		return (NULL);

	// Creates pipe node
	node_pipe2 = node_pip_create(node_c2, node_sub);
	if (node_pipe2 == NULL)
		return (NULL);

	// Creates pipe node
	node_pipe1 = node_pip_create(node_c1, node_pipe2);
	if (node_pipe1 == NULL)
		return (NULL);

	return (node_pipe1);
}

/*
 *	Returns an AST for the command: "cat /dev/urandom | head -1"
 */
static t_node	*ast_create15(void)
{
	t_node	*node_c1;
	t_node	*node_c2;
	t_node	*node_pipe;

	// Creates node_c1
	node_c1 = node_cmd_create("cat /dev/urandom");
	if (node_c1 == NULL)
		return (NULL);
	
	// Creates node_c2
	node_c2 = node_cmd_create("head -1");
	if (node_c2 == NULL)
		return (NULL);

	// Creates pipe node
	node_pipe = node_pip_create(node_c1, node_c2);
	if (node_pipe == NULL)
		return (NULL);

	return (node_pipe);
}


t_node	*ast_create(int nb)
{
	if (nb == 1)
		return (ast_create1());
	else if (nb == 2)
		return (ast_create2());
	else if (nb == 3)
		return (ast_create3());
	else if (nb == 4)
		return (ast_create4());
	else if (nb == 5)
		return (ast_create5());
	else if (nb == 6)
		return (ast_create6());
	else if (nb == 7)
		return (ast_create7());
	else if (nb == 8)
		return (ast_create8());
	else if (nb == 9)
		return (ast_create9());
	else if (nb == 10)
		return (ast_create10());
	else if (nb == 11)
		return (ast_create11());
	else if (nb == 12)
		return (ast_create12());
	else if (nb == 13)
		return (ast_create13());
	else if (nb == 14)
		return (ast_create14());
	else if (nb == 15)
		return (ast_create15());
	return (NULL);
}
