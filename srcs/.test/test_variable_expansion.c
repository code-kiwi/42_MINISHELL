/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_variable_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:23:58 by brappo            #+#    #+#             */
/*   Updated: 2024/04/05 10:59:17 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t	expand_variable(char **input, size_t variable_start);

typedef struct s_test
{
	char	*string;
	size_t	variable_index;
}	t_test;

void	t_test_init(t_test *test, char *string, size_t variable_index)
{
	test->string = ft_strdup(string);
	test->variable_index = variable_index;
}

void	get_tests_basic(char **tests)
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

void	get_advanced_tests(t_test *advanced_tests)
{
	t_test_init(advanced_tests + 0, "  $est ", 2);
	t_test_init(advanced_tests + 1, "qwexoij", 0);
	t_test_init(advanced_tests + 2, "$est", 2);
	t_test_init(advanced_tests + 3, "", 2);
	t_test_init(advanced_tests + 4, "", 0);
	t_test_init(advanced_tests + 5, NULL, 0);
	t_test_init(advanced_tests + 6, "$qwxe", 1566);
	t_test_init(advanced_tests + 7, "$qwxe qwexqwxe", 0);
	t_test_init(advanced_tests + 8, "qwexh$qwxe", 5);
	t_test_init(advanced_tests + 9, "qwexqwelll$qwxe qwex", 10);
	t_test_init(advanced_tests + 10, "${qwxe}", 0);
	t_test_init(advanced_tests + 11, "${qwxe}qwexqwex", 0);
	t_test_init(advanced_tests + 12, "${qwxe}  qwexiu", 0);
	t_test_init(advanced_tests + 13, "qwekjhqx${qwxe}", 8);
	t_test_init(advanced_tests + 14, "qwekjhqx${q_wxe}", 8);
}

void	get_final_tests(char **tests)
{
	tests[0] = ft_strdup("$test");
	tests[1] = ft_strdup("qweixugqw $test qwexh");
	tests[2] = ft_strdup("$test oqjweoijx");
	tests[3] = ft_strdup("qweiuxhq $test");
	tests[4] = ft_strdup("");
	tests[5] = NULL;
	tests[6] = ft_strdup("qiuhwex${qwex}qweuxh");
	tests[7] = ft_strdup("${teuyge}");
	tests[8] = ft_strdup("     ${qwxe}");
	tests[9] = ft_strdup("${iuhqwex}    ");
	tests[10] = ft_strdup("$qwex$qwex  qe${qqhwxe}${iqhwex}${qiexq}qeqxe");
}

int	main(void)
{
	char	*tests_basic[16];
	t_test	advanced_tests[15];
	char	*final_tests[11];
	size_t	index;

	index = 0;
	get_tests_basic(tests_basic);
	printf("\n##########BASIC##########\n\n");
	while (index < 16)
	{
		printf("%sinput : %s%s%s\n", BLUE, tests_basic[index], RESET, GREEN);
		printf("%s", RESET);
		expand_variable(tests_basic + index, 0);
		if (tests_basic[index] != NULL)
			free(tests_basic[index]);
		write(STDOUT_FILENO, "\n", 1);
		index++;
	}
	index = 0;
	get_advanced_tests(advanced_tests);
	printf("\n##########ADVANCED##########\n\n");
	while (index < 15)
	{
		printf("%sinput : %s\nvariable index : %ld%s%s\n", BLUE, advanced_tests[index].string, advanced_tests[index].variable_index, RESET, GREEN);
		printf("%s", RESET);
		expand_variable(&advanced_tests[index].string, advanced_tests[index].variable_index);
		if (advanced_tests[index].string != NULL)
			free(advanced_tests[index].string);
		write(STDOUT_FILENO, "\n", 1);
		index++;
	}
	index = 0;
	get_final_tests(final_tests);
	printf("\n##########FINAL##########\n\n");
	while (index < 11)
	{
		printf("%sinput : %s%s%s\n", BLUE, final_tests[index], RESET, GREEN);
		printf("%s", RESET);
		expand_string(final_tests + index);
		if (final_tests[index] != NULL)
			free(final_tests[index]);
		write(STDOUT_FILENO, "\n", 1);
		index++;
	}
}