/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:10:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/13 21:47:39 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

#include "libft.h"
#include "minishell.h"
#include "env.h"
#include "token.h"
#include "node.h"
#include "prompt.h"
#include "pid_list.h"

/*
 *	Initializes the given shell with empty fields
 *	Then uses the given envp to initialize the shell's env member
 */
void	t_minishell_init(t_minishell *shell, int argc, char **argv, char **envp)
{
	if (shell == NULL)
		return ;
	ft_memset(shell, 0, sizeof(t_minishell));
	shell->env = t_minishell_env_init(envp);
	if (shell->env == NULL)
		handle_error(shell, ERROR_MSG_ENV_CREATION, EXIT_FAILURE);
	(void)argc;
	(void)argv;
	built_in_init_array(shell->bi_funcs);
	shell->is_a_tty = isatty(STDIN_FILENO);
	if (errno == ENOTTY)
		errno = 0;
}

/*
 *	Frees all the resources used by the given shell
 *	NB:
 *		- if the shell is_child process is true, the shell's pid_list elements
 *		are not subjected to the waitpid() calls
 *		- if the shell's parent member is not NULL, the parents are freed using
 *		recursive call to t_minishell_free()
 */
void	t_minishell_free(t_minishell *shell)
{
	rl_clear_history();
	read_one_line(NULL);
	if (shell == NULL)
		return ;
	if (shell->parent != NULL)
		t_minishell_free(shell->parent);
	if (shell->input)
		free(shell->input);
	if (shell->env != NULL)
		ft_lstclear(&(shell->env), env_element_free);
	if (shell->tokens)
		ft_lstclear(&shell->tokens, t_token_free);
	if (shell->pid_list != NULL)
	{
		if (shell->is_child_process)
			pid_list_clear(&(shell->pid_list));
		else
			t_minishell_set_exec_status(shell);
	}
	if (shell->ast != NULL)
		ast_free(&(shell->ast));
}

/*
 *	Initializes the given subshell using the information from its given parent
 *	The subshell's members are set with their default values but the env member
 *	is "stolen" from the parent
 *	The parent member is also initialized
 */
void	t_minishell_init_subshell(t_minishell *sub, t_minishell *parent)
{
	if (sub == NULL || parent == NULL)
		return ;
	ft_memset(sub, 0, sizeof(t_minishell));
	sub->env = parent->env;
	parent->env = NULL;
	sub->parent = parent;
	built_in_init_array(sub->bi_funcs);
	sub->is_a_tty = isatty(STDIN_FILENO);
	if (errno == ENOTTY)
		errno = 0;
}

/*
 *	Resets the given shell
 *	Steps:
 *		- checks the given shell arg
 *		- clears the shell's token list
 *		- clears the shell's AST
 *		- clears the shell's input
 *	In case of ERROR (wrong arg), closes the current shell displaying an error
 *	message.
 */
void	utils_reset_shell(t_minishell *shell, int status)
{
	if (shell == NULL)
		handle_error(shell, ERROR_MSG_ARGS, EXIT_FAILURE);
	errno = 0;
	ft_lstclear(&shell->tokens, t_token_free);
	ast_free(&(shell->ast));
	if (shell->input != NULL)
	{
		if (!string_contains_only_spaces(shell->input) && shell->is_a_tty)
			add_history(shell->input);
		free(shell->input);
		shell->input = NULL;
	}
	shell->heredoc_interruption = false;
	shell->status = status;
}
