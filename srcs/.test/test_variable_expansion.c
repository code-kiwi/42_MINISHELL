/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_variable_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:23:58 by brappo            #+#    #+#             */
/*   Updated: 2024/04/26 16:25:35 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "minishell.h"
#include "env.h"
#include "prompt.h"
#include "expansion.h"

void	echo_string(char *str, char **envp, char *result_perso);

ssize_t	expand_variable(char **input, size_t variable_start,
	bool double_quoted, t_minishell *shell);

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
	tests[1] = ft_strdup("$HOME");
	tests[2] = ft_strdup("$HOME ");
	tests[3] = ft_strdup("${USER}");
	tests[4] = ft_strdup("");
	tests[5] = ft_strdup("$");
	tests[6] = ft_strdup("$HOME");
	tests[7] = NULL;
	tests[8] = ft_strdup("${    qwexi }");
	tests[9] = ft_strdup("$ ");
	tests[10] = ft_strdup("$USER qweoxu");
	tests[11] = ft_strdup("${}");
	tests[12] = ft_strdup("${qweih2594894_qwex_}");
	tests[13] = ft_strdup("${qweih2594894_q-wex_}");
	tests[14] = ft_strdup("${qwei h2594894_qwex_}");
	tests[15] = ft_strdup("${ }");
}

void	get_advanced_tests(t_test *advanced_tests)
{
	t_test_init(advanced_tests + 0, "  $HOME ", 2);
	t_test_init(advanced_tests + 1, "qwexoij", 0);
	t_test_init(advanced_tests + 2, "$USER", 2);
	t_test_init(advanced_tests + 3, "", 2);
	t_test_init(advanced_tests + 4, "", 0);
	t_test_init(advanced_tests + 5, NULL, 0);
	t_test_init(advanced_tests + 6, "$HOME", 1566);
	t_test_init(advanced_tests + 7, "$USER qwexqwxe", 0);
	t_test_init(advanced_tests + 8, "qwexh$qwxe", 5);
	t_test_init(advanced_tests + 9, "qwexqwelll$qwxe qwex", 10);
	t_test_init(advanced_tests + 10, "${HOME}", 0);
	t_test_init(advanced_tests + 11, "${HOME}qwexqwex", 0);
	t_test_init(advanced_tests + 12, "${USER}  qwexiu", 0);
	t_test_init(advanced_tests + 13, "qwekjhqx${HOME}", 8);
	t_test_init(advanced_tests + 14, "qwekjhqx${q_wxe}", 8);
}

void	get_final_tests(char **tests)
{
	tests[0] = ft_strdup("$HOME");
	tests[1] = ft_strdup("qweixugqw $USER qwexh");
	tests[2] = ft_strdup("$HOME oqjweoijx");
	tests[3] = ft_strdup("qweiuxhq $USER");
	tests[4] = ft_strdup("");
	tests[5] = NULL;
	tests[6] = ft_strdup("qiuhwex${HOME}qweuxh");
	tests[7] = ft_strdup("${USER}");
	tests[8] = ft_strdup("     ${HOME}");
	tests[9] = ft_strdup("${HOME}    ");
	tests[10] = ft_strdup("$USER  qe${HOME}${USER}${HOME}qeqxe");
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
	char		*tests_basic[16];
	t_test		advanced_tests[15];
	char		*final_tests[39];
	size_t		index;
	t_minishell	shell;
	char		*str_copy;

	t_minishell_init(&shell, argc, argv, envp);
	env_add(&shell.env, "?", "0");
	index = 0;
	get_tests_basic(tests_basic);
	printf("\n##########BASIC##########\n\n");
	while (index < 16)
	{
		printf("%sinput : %s%s%s\n", BLUE, tests_basic[index], RESET, GREEN);
		printf("%s", RESET);
		expand_variable(tests_basic + index, 0, false, &shell);
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
		expand_variable(&advanced_tests[index].string, advanced_tests[index].variable_index, false, &shell);
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
		str_copy = ft_strdup(final_tests[index]);
		expand_string(final_tests + index, &shell, O_PATH | O_VAR | O_QUOTE);
		printf("result final : %s\n", final_tests[index]);
		echo_string(str_copy, envp, final_tests[index]);
		free(str_copy);
		if (final_tests[index] != NULL)
			free(final_tests[index]);
		write(STDOUT_FILENO, "\n", 1);
		index++;
	}
	t_minishell_free(&shell);
}
