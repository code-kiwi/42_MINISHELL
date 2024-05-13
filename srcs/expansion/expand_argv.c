/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:24:26 by brappo            #+#    #+#             */
/*   Updated: 2024/05/13 10:11:13 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "minishell.h"
#include "expansion.h"
#include "errno.h"
#include "libft.h"

static void	cat_lst_in_array(char **array_dest, t_list *lst_src,
	size_t start, size_t length)
{
	if (array_dest == NULL || lst_src == NULL)
		return ;
	while (lst_src != NULL && start < length)
	{
		array_dest[start] = (char *)lst_src->content;
		start++;
		lst_src = lst_src->next;
	}
}

static char	**insert_list_in_array(char **array, t_list *lst,
	size_t index, size_t array_length)
{
	size_t	result_length;
	size_t	list_length;
	char	**new_array;

	list_length = ft_lstsize(lst);
	result_length = array_length + list_length;
	new_array = (char **)ft_calloc(result_length + 2, sizeof(char *));
	if (new_array == NULL)
		return (NULL);
	array_cat((void **)new_array, (void **)array, result_length + 2);
	cat_lst_in_array(new_array, lst, index, result_length + 1);
	array_cat((void **)new_array, (void **)array + index, result_length + 2);
	return (new_array);
}

static bool	replace_arguments(char ***argv,
	t_list *wildcards_candidates, size_t arg_index)
{
	char	**new_argv;
	size_t	array_length;

	if (argv == NULL || wildcards_candidates == NULL)
		return (true);
	array_length = array_size((void **)*argv);
	if (arg_index > array_length)
		return (false);
	free((*argv)[arg_index]);
	ft_memcpy(*argv + arg_index, *argv + arg_index + 1,
		(array_length - arg_index) * sizeof(char *));
	(*argv)[array_length - 1] = NULL;
	new_argv = insert_list_in_array(*argv, wildcards_candidates,
			arg_index, array_length - 2);
	if (new_argv == NULL)
		return (false);
	free(*argv);
	*argv = new_argv;
	return (true);
}

bool	expand_redirection(char **redirection, char options, t_minishell *shell)
{
	t_list	*wildcards_candidate;
	char	*save;

	save = ft_strdup(*redirection);
	if (save == NULL)
		return (false);
	wildcards_candidate = expand_string(redirection, shell, options);
	if (ft_lstsize(wildcards_candidate) > 1)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s\n", save, ERROR_MSG_AMBIG_REDIR);
		free(save);
		ft_lstclear(&wildcards_candidate, free);
		return (false);
	}
	free(save);
	if (wildcards_candidate == NULL && errno != 0)
		return (false);
	if (wildcards_candidate == NULL)
		return (true);
	free(*redirection);
	*redirection = wildcards_candidate->content;
	free(wildcards_candidate);
	return (true);
}

bool	expand_argv(char ***argv, char options, t_minishell *shell)
{
	size_t	index;
	t_list	*wildcards_candidate;
	size_t	candidates_count;

	if (argv == NULL || *argv == NULL)
		return (false);
	index = 0;
	while ((*argv)[index])
	{
		wildcards_candidate = expand_string(*argv + index, shell, options);
		if (errno != 0 || !replace_arguments(argv, wildcards_candidate, index))
		{
			ft_lstclear(&wildcards_candidate, free);
			return (false);
		}
		candidates_count = ft_lstsize(wildcards_candidate);
		if (candidates_count != 0)
			index += candidates_count - 1;
		ft_lstclear(&wildcards_candidate, NULL);
		index++;
	}
	return (true);
}
