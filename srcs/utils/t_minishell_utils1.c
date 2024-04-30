/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:10:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/30 18:32:35 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include "libft.h"
#include "minishell.h"
#include "env.h"
#include "token.h"
#include "node.h"
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
	shell->env = env_extract(envp);
	(void)argc;
	(void)argv;
	shell->input = NULL;
	shell->tokens = NULL;
	shell->pid_list = NULL;
	shell->is_child_process = false;
	shell->status = 0;
	built_in_init_array(shell->bi_funcs);
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
	get_next_line(-1);
	rl_clear_history();
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
			t_minishell_get_exec_status(shell);
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
	t_minishell_init(sub, 0, NULL, NULL);
	sub->env = parent->env;
	parent->env = NULL;
	sub->parent = parent;
}
