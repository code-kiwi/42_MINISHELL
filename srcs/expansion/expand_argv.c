/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:24:26 by brappo            #+#    #+#             */
/*   Updated: 2024/04/29 12:12:20 by brappo           ###   ########.fr       */
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

static char	**insert_list_array_str(char **array, t_list *lst,
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
	new_argv = insert_list_array_str(*argv, wildcards_candidates,
			arg_index, array_length - 1);
	if (new_argv == NULL)
		return (false);
	free(*argv);
	*argv = new_argv;
	return (true);
}

static bool	handle_redirection_error(t_list *wildcards_candidate,
	bool is_redirection, char *save)
{
	if (is_redirection && ft_lstsize(wildcards_candidate) > 1)
	{
		printf("Ambiguous redirection : %s\n", save);
		free(save);
		ft_lstclear(&wildcards_candidate, free);
		return (false);
	}
	return (true);
}

bool	expand_argv(char ***argv, char options,
		t_minishell *shell, bool is_redirection)
{
	size_t	index;
	t_list	*wildcards_candidate;
	char	*save;

	if (argv == NULL || *argv == NULL)
		return (false);
	index = 0;
	while ((*argv)[index])
	{
		save = ft_strdup((*argv)[index]);
		if (save == NULL)
			return (false);
		wildcards_candidate = expand_string(*argv + index, shell, options);
		if (!handle_redirection_error(wildcards_candidate,
				is_redirection, save))
			return (false);
		free(save);
		if (!replace_arguments(argv, wildcards_candidate, index) && errno != 0)
			return (ft_lstclear(&wildcards_candidate, free), false);
		ft_lstclear(&wildcards_candidate, NULL);
		index++;
	}
	return (true);
}
