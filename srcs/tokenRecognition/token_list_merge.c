/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_merge.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:42:20 by root              #+#    #+#             */
/*   Updated: 2024/05/10 17:01:26 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "libft.h"
#include "minishell.h"
#include "token.h"

/*
	When merging tokens, the "next" string is joined with the "first" string.
	The next value of "first" is set to the next value of "next".
	The next value of "first" has to be NULL, otherwise, memory could be lost,
	the function just return false in that case.
	It is useful when a command is split on multiples lines, and a word is split
	in different token list, this function allow to joined these words in one.
	ex :	first : echo 7aze"

			second : azex"
			->
			return : echo 7"aze
							azex"
	Working.
*/
static bool	merge_tokens_node(t_list *first, t_list *next)
{
	t_token	*first_token;
	t_token	*next_token;

	first_token = (t_token *)(first->content);
	if (first == NULL || first->next != NULL)
		return (false);
	if (next == NULL)
	{
		if (join_into_dest(&first_token->str, "\n") == NULL)
			return (false);
	}
	else
	{
		next_token = (t_token *)(next->content);
		if (bridge_into_first(&first_token->str, next_token->str, "\n") == NULL)
			return (false);
		first->next = next->next;
		ft_lstdelone(next, t_token_free);
	}
	return (true);
}

bool	append_token_list(bool is_first_quoted, t_list **first, t_list *second)
{
	t_list	*last_node;

	if (first == NULL)
		return (false);
	if (*first == NULL)
	{
		*first = second;
		return (true);
	}
	last_node = ft_lstlast(*first);
	if (is_first_quoted == true)
	{
		if (merge_tokens_node(last_node, second) == false)
			return (false);
	}
	else
		last_node->next = second;
	return (true);
}
