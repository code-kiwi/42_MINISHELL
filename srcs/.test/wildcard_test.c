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

#define TEST_OK_NUMBER 13
#define TEST_KO_NUMBER 7

bool	quote_removal(char **input, t_minishell *shell, t_list **wildcards_pos);

void	print_pointeur(void *pointeur)
{
	printf("%p\n", pointeur);
}

bool	equals(char *str_wildcard, char *b)
{
	t_list	*wildcard_pos;
	bool	result;

	if (quote_removal(&str_wildcard, NULL, &wildcard_pos) == false)
	{
		printf("ERROR");
		return (false);
	}
	result = string_equal_wildcard(str_wildcard, b, wildcard_pos);
	ft_lstclear(&wildcard_pos, NULL);
	return (result);
}

void	get_tests_ok(char **tests)
{
	tests[0] = ft_strdup("test");
	tests[1] = ft_strdup("test");
	tests[2] = ft_strdup("test*");
	tests[3] = ft_strdup("test");
	tests[4] = ft_strdup("*test");
	tests[5] = ft_strdup("test");
	tests[6] = ft_strdup("*test*");
	tests[7] = ft_strdup("test");
	tests[8] = ft_strdup("*est");
	tests[9] = ft_strdup("test");
	tests[10] = ft_strdup("*est");
	tests[11] = ft_strdup("qexgqwexyqhiuwehxuqhwxest");
	tests[12] = ft_strdup("je*suis*un*test");
	tests[13] = ft_strdup("jeqwexsuisiqjwxeunqoiwxetest");
	tests[14] = ft_strdup("je*suis*un*test");
	tests[15] = ft_strdup("jesuisuntest");
	tests[16] = ft_strdup("machin***e");
	tests[17] = ft_strdup("machine");
	tests[18] = ft_strdup("i*ude");
	tests[19] = ft_strdup("include");
	tests[20] = ft_strdup("i*des*");
	tests[21] = ft_strdup("includesfile");
	tests[22] = ft_strdup("test****s*characteres");
	tests[23] = ft_strdup("test sur plusieurs characteres");
	tests[24] = ft_strdup("test\"*\"");
	tests[25] = ft_strdup("test*");
}

void	get_tests_ko(char **tests)
{
	tests[0] = ft_strdup("teste");
	tests[1] = ft_strdup("test");
	tests[2] = ft_strdup("truc");
	tests[3] = ft_strdup("machin");
	tests[4] = ft_strdup("i*clude");
	tests[5] = ft_strdup("includes");
	tests[6] = ft_strdup("test sur plusieurs characteresA");
	tests[7] = ft_strdup("test sur plusieurs characteresB");
	tests[8] = ft_strdup("test sur plusieurs characteres");
	tests[9] = ft_strdup("test sur plusieurs characteresC");
	tests[10] = ft_strdup("test*sur*plusieurs*characteres");
	tests[11] = ft_strdup("test sur plusieurscharacteresA");
	tests[12] = ft_strdup("autre test");
	tests[13] = ft_strdup("autre testoijqx");
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
		free(tests_OK[index * 2]);
		free(tests_OK[index * 2 + 1]);
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
		free(tests_KO[index * 2]);
		free(tests_KO[index * 2 + 1]);
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
