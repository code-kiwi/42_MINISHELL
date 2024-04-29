/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:24:26 by brappo            #+#    #+#             */
/*   Updated: 2024/04/29 12:38:33 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
#include "errno.h"
#include "libft.h"
#include <stdio.h>

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
	new_array = (char **)ft_calloc(result_length + 1, sizeof(char *));
	if (new_array == NULL)
		return (NULL);
	array_copy((void ***)new_array, (void ***)*array, index);
	cat_lst_in_array(new_array, lst, array_length, result_length);
	array_copy((void ***)new_array + index + list_length,
		(void ***)*array, array_length);
	return (new_array);
}

static bool	replace_arguments(char ***argv,
	t_list *wildcards_candidates, size_t arg_index)
{
	char	**new_argv;
	size_t	array_length;

	if (argv == NULL || wildcards_candidates == NULL)
		return (false);
	array_length = array_size((void **)*argv);
	if (arg_index > array_length)
		return (false);
	free((*argv)[arg_index]);
	ft_memmove(*argv + arg_index, *argv + arg_index + 1, array_length + 1);
	new_argv = insert_list_in_array(*argv, wildcards_candidates,
			arg_index, array_length - 1);
	if (new_argv == NULL)
		return (false);
	free(*argv);
	*argv = new_argv;
	return (true);
}

bool	expand_redirection(char **redirection, char options,
	t_minishell *shell)
{
	t_list	*wildcards_candidate;
	char	*save;

	save = ft_strdup(*redirection);
	if (save == NULL)
		return (false);
	wildcards_candidate = expand_string(redirection, shell, options);
	if (wildcards_candidate == NULL && errno != 0)
		return (free(save), false);
	if (wildcards_candidate == NULL)
		return (free(save), true);
	if (ft_lstsize(wildcards_candidate) > 1)
	{
		printf("%s %s\n", save, AMBIGUOUS_REDIRECTION);
		free(save);
		ft_lstclear(&wildcards_candidate, free);
		return (false);
	}
	free(save);
	free(*redirection);
	*redirection = wildcards_candidate->content;
	free(wildcards_candidate);
	return (true);
}

bool	expand_argv(char ***argv, char options,
		t_minishell *shell)
{
	size_t	index;
	t_list	*wildcards_candidate;

	if (argv == NULL || *argv == NULL)
		return (false);
	index = 0;
	while ((*argv)[index])
	{
		wildcards_candidate = expand_string(*argv + index, shell, options);
		if (!replace_arguments(argv, wildcards_candidate, index) && errno != 0)
		{
			ft_lstclear(&wildcards_candidate, free);
			return (false);
		}
		ft_lstclear(&wildcards_candidate, NULL);
		index++;
	}
	return (true);
}