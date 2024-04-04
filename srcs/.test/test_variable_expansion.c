/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_variable_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:23:58 by brappo            #+#    #+#             */
/*   Updated: 2024/04/04 14:19:57 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_variable_key_coordinates(char *input, ssize_t *coordinates);

void	get_tests(char **tests)
{
	tests[0] = ft_strdup("test");
	tests[1] = ft_strdup("$test");
	tests[2] = ft_strdup("$test ");
	tests[3] = ft_strdup("${test}");
	tests[4] = ft_strdup("");
	tests[5] = ft_strdup("$");
	tests[6] = ft_strdup("$a");
	tests[7] = NULL;
	tests[8] = ft_strdup("${    qwexi }");
	tests[9] = ft_strdup("$ ");
	tests[10] = ft_strdup("$qwex qweoxu");
	tests[11] = ft_strdup("${}");
	tests[12] = ft_strdup("${qweih2594894_qwex_}");
	tests[13] = ft_strdup("${qweih2594894_q-wex_}");
	tests[14] = ft_strdup("${qwei h2594894_qwex_}");
	tests[15] = ft_strdup("${ }");
}

int	main(void)
{
	char	*tests[16];
	size_t	index;

	index = 0;
	get_tests(tests);
	while (index < 16)
	{
		printf("%sinput : %s%s%s\n", BLUE, tests[index], RESET, GREEN);
		printf("%s", RESET);
		expand_variable(tests[index]);
		if (tests[index] != NULL)
			free(tests[index]);
		write(STDOUT_FILENO, "\n", 1);
		index++;
	}
}