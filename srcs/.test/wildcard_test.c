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

#define TEST_NUMBER 18

bool	string_equal_wildcard(char *str_wildcard, char *str_b);

void	get_tests(char **tests)
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
	tests[12] = "truc";
	tests[13] = "machin";
	tests[14] = "je*suis*un*test";
	tests[15] = "jeqwexsuisiqjwxeunqoiwxetest";
	tests[16] = "je*suis*un*test";
	tests[17] = "jesuisuntest";
	tests[18] = "autre test";
	tests[19] = "autre testoijqx";
	tests[20] = "machin***e";
	tests[21] = "machine";
	tests[22] = "i*ude";
	tests[23] = "include";
	tests[24] = "i*clude";
	tests[25] = "includes";
	tests[26] = "i*des*";
	tests[27] = "includesfile";
	tests[28] = "test sur plusieurs characteresA";
	tests[29] = "test sur plusieurs characteresB";
	tests[30] = "test sur plusieurs characteres";
	tests[31] = "test sur plusieurs characteresC";
	tests[32] = "test****s*characteres";
	tests[33] = "test sur plusieurs characteres";
	tests[34] = "test*sur*plusieurs*characteres";
	tests[35] = "test sur plusieurscharacteresA";
}

// int	main()
// {
// 	char	*tests[TEST_NUMBER * 2];
// 	size_t	index;

// 	index = 0;
// 	get_tests(tests);
// 	while (index < TEST_NUMBER)
// 	{
// 		printf("%s equals %s ? : %s\n", tests[index * 2], tests[index * 2 + 1], string_equal_wildcard(tests[index * 2], tests[index * 2 + 1]) ? "true" : "false");
// 		index++;
// 	}
// 	return (0);
// }

int	main(int argc, char **argv)
{
	char	*result;

	if (argc != 2)
		return (printf("need 2 arguments"), 1);
	result = expand_wildcard(argv[1]);
	printf("%s\n", result);
	free(result);
	return (0);
}
