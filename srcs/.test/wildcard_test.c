/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:51:37 by brappo            #+#    #+#             */
/*   Updated: 2024/04/11 16:38:49y brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define TEST_OK_NUMBER 12
#define TEST_KO_NUMBER 7

bool	quote_removal(char **input, t_minishell *shell, t_list **wildcards_pos);

bool	equals(char *str_wildcard, char *b)
{
	t_list	*wildcard_pos;

	if (quote_removal(&str_wildcard, NULL, &wildcard_pos) == false)
	{
		printf("ERROR");
		return (false);
	}
	return (string_equal_wildcard(str_wildcard, b, wildcard_pos));
}

void	get_tests_ok(char **tests)
{
	tests[0] = "test";
	tests[1] = "test";
	tests[2] = "test*";
	tests[3] = "test";
	tests[4] = "*test";
	tests[5] = "test";
	tests[6] = "*test*";
	tests[7] = "test";
	tests[8] = "*est";
	tests[9] = "test";
	tests[10] = "*est";
	tests[11] = "qexgqwexyqhiuwehxuqhwxest";
	tests[12] = "je*suis*un*test";
	tests[13] = "jeqwexsuisiqjwxeunqoiwxetest";
	tests[14] = "je*suis*un*test";
	tests[15] = "jesuisuntest";
	tests[16] = "machin***e";
	tests[17] = "machine";
	tests[18] = "i*ude";
	tests[19] = "include";
	tests[20] = "i*des*";
	tests[21] = "includesfile";
	tests[22] = "test****s*characteres";
	tests[23] = "test sur plusieurs characteres";
}

void	get_tests_ko(char **tests)
{
	tests[0] = "teste";
	tests[1] = "test";
	tests[2] = "truc";
	tests[3] = "machin";
	tests[4] = "i*clude";
	tests[5] = "includes";
	tests[6] = "test sur plusieurs characteresA";
	tests[7] = "test sur plusieurs characteresB";
	tests[8] = "test sur plusieurs characteres";
	tests[9] = "test sur plusieurs characteresC";
	tests[10] = "test*sur*plusieurs*characteres";
	tests[11] = "test sur plusieurscharacteresA";
	tests[12] = "autre test";
	tests[13] = "autre testoijqx";
}

void	run_tests()
{
	char	*tests_OK[TEST_OK_NUMBER * 2];
	char	*tests_KO[TEST_KO_NUMBER * 2];
	bool	result;
	size_t	index;

	index = 0;
	printf("%s#########VALID TESTS############%s\n\n", GREEN, RESET);
	get_tests_ok(tests_OK);
	while (index < TEST_OK_NUMBER)
	{
		printf("%s%s%s equals %s%s%s ? : ", BLUE, tests_OK[index * 2], RESET, BLUE, tests_OK[index * 2 + 1], RESET);
		result = equals(tests_OK[index * 2], tests_OK[index * 2 + 1]);
		if (result)
			printf("%strue%s\n\n", GREEN, RESET);
		else
			printf("%sfalse%s\n\n", RED, RESET);
		index++;
	}
	index = 0;
	printf("%s#########ERROR TESTS############%s\n\n", RED, RESET);
	get_tests_ko(tests_KO);
	while (index < TEST_KO_NUMBER)
	{
		printf("%s%s%s equals %s%s%s ? : ", BLUE, tests_KO[index * 2], RESET, BLUE, tests_KO[index * 2 + 1], RESET);
		result = equals(tests_KO[index * 2], tests_KO[index * 2 + 1]);
		if (result)
			printf("%strue%s\n\n", GREEN, RESET);
		else
			printf("%sfalse%s\n\n", RED, RESET);
		index++;
	}
}

int	main(int argc, char **argv)
{
	char	*test;
	t_list	*result;

	if (argc != 2)
	{
		run_tests();
		return (0);
	}
	test = ft_strdup(argv[1]);
	result = expand_string(&test, NULL);
	if (result == NULL)
	{
		printf("ERROR");
		return (1);
	}
	ft_lstprint(result, print_token);
	ft_lstclear(&result, t_token_free);
	free(test);
	return (0);
}
