/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:24:26 by brappo            #+#    #+#             */
/*   Updated: 2024/04/29 10:32:46 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	**insert_list_array_str(char **array, t_list *lst,
	size_t index, size_t array_length)
{
	size_t	result_length;
	size_t	list_length;
	char	**new_array;

	if (index > array_length)
		return (NULL);
	list_length = ft_lstsize(lst);
	result_length = array_length + list_length;
	new_array = (char **)ft_calloc(result_length + 1, sizeof(char *));
	if (new_array == NULL)
		return (NULL);
	array_copy((void ***)new_array, (void ***)*array, index);
	cat_lst_in_array(new_array, lst, array_length, result_length);
	array_copy((void ***)new_array + index + list_length, (void ***)*array, array_length);
	return (new_array);
}

static void	delete_elem(char **argv, size_t elem_index, size_t array_length)
{
	free(*argv + elem_index);
	(*argv)[elem_index] == NULL;
	ft_memmove(*argv + elem_index, *argv + elem_index+ 1, array_length + 1);
}

static bool	replace_arguments(char ***argv, t_list *wildcards_candidates, size_t arg_index)
{
	char	**new_argv;
	size_t	array_length;

	if (argv == NULL || wildcards_candidates == NULL)
		return (false);
	if (wildcards_candidates == NULL)
		return (true);
	array_length = array_size(*argv);
	delete_elem(*argv, arg_index, array_length);
	new_argv = insert_list_array_str(*argv, wildcards_candidates, arg_index, array_length);
	if (new_argv == NULL)
		return (false);
	free(*argv);
	*argv = new_argv;
	return (true);
}

bool	expand_argv(char ***argv, char options, t_minishell *shell, bool is_redirection)
{
	size_t	index;
	t_list	*wildcards_candidate;

	if (argv == NULL || *argv == NULL)
		return (false);
	index = 0;
	while ((*argv)[index])
	{
		wildcards_candidate = expand_string((*argv)[index], shell, options);
		if (wildcards_candidate == NULL && errno != 0)
			return (false);
		if ((is_redirection && ft_lstsize(wildcards_candidate) > 1)
			|| !replace_arguments(argv, wildcards_candidate, index))
		{
			ft_lstclear(&wildcards_candidate, free);
			return (false);
		}
		ft_lstclear(&wildcards_candidate, NULL);
		index++;
	}
	return (true);
}