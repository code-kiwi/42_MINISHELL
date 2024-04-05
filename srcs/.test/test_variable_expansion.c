/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_variable_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:23:58 by brappo            #+#    #+#             */
/*   Updated: 2024/04/05 13:42:25 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

void	echo_string(char *str, char **envp)
{
	pid_t	pid;
	int		tube[2];
	char	*argv[2];

	argv[0] = "/usr/bin/bash";
	argv[1] = NULL;
	pipe(tube);
	write(tube[1], "echo ", 5);
	write(tube[1], str, ft_strlen(str));
	close(tube[1]);
	pid = fork();
	if (pid == 0)
	{
		write(STDIN_FILENO, "bash : ", 7);
		dup2(tube[0], STDIN_FILENO);
		close(tube[0]);
		execve(argv[0], argv, envp);
	}
	else
	{
		wait(NULL);
	}
}

ssize_t	expand_variable(char **input, size_t variable_start, bool double_quoted);

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
	tests[11] = ft_strdup("\"$'home\"");
	tests[12] = ft_strdup("$'home'");
	tests[13] = ft_strdup("$\"home\"");
	//test proposes
	tests[14] = ft_strdup("$\"HOME\"$USER");
	tests[15] = ft_strdup("$\"HOM\"E$USER");
	tests[16] = ft_strdup("$\"'HOM'E\"$USER");
	tests[17] = ft_strdup("$'HOM'E$USER");
	tests[18] = ft_strdup("$\"HOME\"");
	tests[19] = ft_strdup("$'HOME'");
	tests[20] = ft_strdup("$");
	tests[21] = ft_strdup("\"$\"");
	tests[22] = ft_strdup("'$='");
	tests[23] = ft_strdup("\"$\"\"$\"");
	tests[24] = ft_strdup("$\"42$\"");
	tests[25] = ft_strdup("\"$\"$");
	tests[26] = ft_strdup("$'$'");
	tests[27] = ft_strdup("'$'$");
	tests[28] = ft_strdup("\"$ \"");
	tests[29] = ft_strdup("' $'");
	tests[30] = ft_strdup("\"\"$?\"\"");
	tests[31] = ft_strdup("\" \"$?\" \"");
	tests[32] = ft_strdup("$?\"42\"");
	tests[33] = ft_strdup("''$?''\"42\"");
	tests[34] = ft_strdup("'HELLO'$?:''\"42\"");
	tests[35] = ft_strdup("\"$?\"");
	tests[36] = ft_strdup("'$?'");
	tests[37] = ft_strdup("\"'$?'\"");
	tests[38] = ft_strdup("'\"$?\"'");
}

int	main(int argc, char **argv, char **envp)
{
	char	*tests_basic[16];
	t_test	advanced_tests[15];
	char	*final_tests[39];
	size_t	index;

	index = 0;
	if (argc > 1)
		argv[1] = "test";
	get_tests_basic(tests_basic);
	printf("\n##########BASIC##########\n\n");
	while (index < 16)
	{
		printf("%sinput : %s%s%s\n", BLUE, tests_basic[index], RESET, GREEN);
		printf("%s", RESET);
		expand_variable(tests_basic + index, 0, false);
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
		expand_variable(&advanced_tests[index].string, advanced_tests[index].variable_index, false);
		printf("result final : %s\n", advanced_tests[index].string);
		if (advanced_tests[index].string != NULL)
			free(advanced_tests[index].string);
		write(STDOUT_FILENO, "\n", 1);
		index++;
	}
	index = 0;
	get_final_tests(final_tests);
	printf("\n##########FINAL##########\n\n");
	while (index < 39)
	{
		printf("%sinput : %s%s%s\n", BLUE, final_tests[index], RESET, GREEN);
		printf("%s", RESET);
		echo_string(final_tests[index], envp);
		expand_string(final_tests + index);
		printf("result final : %s\n", final_tests[index]);
		if (final_tests[index] != NULL)
			free(final_tests[index]);
		write(STDOUT_FILENO, "\n", 1);
		index++;
	}
}