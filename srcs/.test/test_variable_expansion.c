/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_variable_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:23:58 by brappo            #+#    #+#             */
/*   Updated: 2024/04/04 11:04:06 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	get_variable(char *input);

void	get_tests(char **tests)
{
	tests[0] = ft_strdup("test");
	tests[1] = ft_strdup("$test");
	tests[2] = ft_strdup("$test ");
	tests[3] = ft_strdup("${test}");
}

int	main(void)
{
	char	*tests[4];
	size_t	index;

	index = 0;
	get_tests(tests);
	while (index < 4)
	{
		printf("%sinput : %s%s%s\n", BLUE, tests[index], RESET, GREEN);
		get_variable(tests[index]);
		printf("%s\n", RESET);
		free(tests[index]);
		index++;
	}
}