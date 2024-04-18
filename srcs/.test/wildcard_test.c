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

static bool	remove_quote(char character, t_token_parser *parser)
{
	if (character == '"' && !parser->single_quoted)
	{
		parser->double_quoted = !parser->double_quoted;
		return (true);
	}
	if (character == '\'' && !parser->double_quoted)
	{
		parser->single_quoted = !parser->single_quoted;
		return (true);
	}
	return (false);
}

bool	search_wildcards(char *input, t_list **wildcards_pos)
{
	size_t			index;
	t_token_parser	parser;
	size_t			removed_quote;

	if (!input || !wildcards_pos || *wildcards_pos)
		return (false);
	t_token_parser_init(&parser);
	parser.end = &index;
	index = 0;
	removed_quote = 0;
	while (input[index] != '\0')
	{
		if (remove_quote(input[index], &parser))
			removed_quote += 1;
		else if (input[index] == '*' && !is_quoted(&parser))
		{
			if (!lst_push_front_content(wildcards_pos,
					input + index - removed_quote, NULL))
				return (ft_lstclear(wildcards_pos, NULL), false);
		}
		index++;
	}
	ft_lstreverse(wildcards_pos);
	return (true);
}

void	echo_string(char *str, char **envp, char *result_perso);

void	print_pointeur(void *pointeur)
{
	printf("%p\n", pointeur);
}

bool	equals(char **str_wildcard, char *b, t_minishell *shell)
{
	t_list	*wildcard_pos;
	bool	result;
	t_list	*new_arguments;

	wildcard_pos = NULL;
	if (!search_wildcards(*str_wildcard, &wildcard_pos))
		return (false);
	new_arguments = expand_string(str_wildcard, shell, O_QUOTE);
	if (new_arguments == NULL)
	{
		printf("ERROR\n");
		ft_lstclear(&wildcard_pos, NULL);
		return (false);
	}
	result = string_equal_wildcard(*str_wildcard, b, wildcard_pos);
	ft_lstclear(&wildcard_pos, NULL);
	ft_lstclear(&new_arguments, free);
	return (result);
}

#define TEST_OK_NUMBER 26
#define TEST_KO_NUMBER 11
#define TEST_FINALS_NUMBER 12

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
	tests[26] = ft_strdup("*\"*\"");
	tests[27] = ft_strdup("machintruc*");
	tests[28] = ft_strdup("\'*\'*");
	tests[29] = ft_strdup("*");
	tests[30] = ft_strdup("*echo'*'");
	tests[31] = ft_strdup("machinecho*");
	tests[32] = ft_strdup("'machin'\"*\"*");
	tests[33] = ft_strdup("machin*iuqwieyxuhqwiuhxeiqwhe");
	tests[34] = ft_strdup("*");
	tests[35] = ft_strdup("'*'");
	tests[36] = ft_strdup("echo'*'truc");
	tests[37] = ft_strdup("echo*truc");
	tests[38] = ft_strdup("*'*'*");
	tests[39] = ft_strdup("echo*truc");
	tests[40] = ft_strdup("ec***truc");
	tests[41] = ft_strdup("echotruc");
	tests[42] = ft_strdup("ec**\"*\"o*");
	tests[43] = ft_strdup("ech*o");
	tests[44] = ft_strdup("***ech***o***");
	tests[45] = ft_strdup("echo");
	tests[46] = ft_strdup("****");
	tests[47] = ft_strdup("oijhazex");
	tests[48] = ft_strdup("iuah*ex'*'");
	tests[49] = ft_strdup("iuahoiazjexuiex*");
	tests[50] = ft_strdup("truc*machin");
	tests[51] = ft_strdup("truc'*'machin");
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
	tests[14] = ft_strdup("ec'*'o");
	tests[15] = ft_strdup("echo");
	tests[16] = ft_strdup("echo\"*\"");
	tests[17] = ft_strdup("echotruc");
	tests[18] = ft_strdup("'*'");
	tests[19] = ft_strdup("machin");
	tests[20] = ft_strdup("machin\"*\"");
	tests[21] = ft_strdup("machintruc");
}

void	get_tests_finals(char **tests, t_minishell *shell)
{
	tests[0] = ft_strdup("*");
	tests[1] = ft_strdup("$HOME");
	tests[2] = ft_strdup("$USER");
	tests[3] = ft_strdup("$biduletruc");
	tests[4] = ft_strdup("conf*");
	tests[5] = ft_strdup("conf");
	tests[6] = ft_strdup("mini*");
	env_add(&shell->env, "minishell", "mini");
	tests[7] = ft_strdup("$minishell");
	tests[8] = ft_strdup("$minishell*");
	tests[9] = ft_strdup("${minishell}shell");
	tests[10] = ft_strdup("$minishellshell");
	env_add(&shell->env, "truc", "ni"),
	tests[11] = ft_strdup("'mi'\"$truc\"*");
}

char	*concatenate_content(t_list *lst)
{
	char	*result;
	t_list	*current;

	if (lst == NULL)
		return (NULL);
	result = ft_strdup((char *)(lst->content));
	current = lst->next;
	while (current != NULL)
	{
		result = bridge_into_first(&result, (char *)current->content, " ");
		current = current->next;
	}
	return (result);
}

void	run_tests(t_minishell *shell)
{
	char	*tests_OK[TEST_OK_NUMBER * 2];
	char	*tests_KO[TEST_KO_NUMBER * 2];
	char	*tests_finals[TEST_FINALS_NUMBER];
	bool	result;
	t_list	*result_lst;
	char	*result_str;
	size_t	index;
	char	**envp;
	char	*temp;

	index = 0;
	printf("%s#########VALID TESTS############%s\n\n", GREEN, RESET);
	get_tests_ok(tests_OK);
	while (index < TEST_OK_NUMBER)
	{
		printf("%s%s%s equals %s%s%s ? : ", BLUE, tests_OK[index * 2], RESET, BLUE, tests_OK[index * 2 + 1], RESET);
		result = equals(&tests_OK[index * 2], tests_OK[index * 2 + 1], shell);
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
		result = equals(&tests_KO[index * 2], tests_KO[index * 2 + 1], shell);
		if (result)
			printf("%strue%s\n\n", GREEN, RESET);
		else
			printf("%sfalse%s\n\n", RED, RESET);
		free(tests_KO[index * 2]);
		free(tests_KO[index * 2 + 1]);
		index++;
	}
	index = 0;
	printf("%s#########FINALS TESTS############%s\n\n", RED, RESET); 
	get_tests_finals(tests_finals, shell);
	envp = env_get_all_array(shell->env);
	while (index < TEST_FINALS_NUMBER)
	{
		temp = ft_strdup(tests_finals[index]);
		printf("%s%s%s\n", BLUE, tests_finals[index], RESET);
		result_lst = expand_string(&tests_finals[index], shell, O_QUOTE | O_PATH | O_VAR);
		result_str = concatenate_content(result_lst);
		echo_string(temp, envp, result_str);
		printf("perso : %s\n", result_str);
		ft_lstclear(&result_lst, free);
		free(result_str);
		free(tests_finals[index]);
		free(temp);
		index++;
	}
	ft_free_str_array(&envp);
}

void	print_str(void *str)
{
	printf("%s\n", (char *)str);
}

int	main(int argc, char **argv, char **envp)
{
	t_list		*result;
	t_list		*tokens;
	t_minishell	shell;
	t_token		*token;

	t_minishell_init(&shell, argc, argv, envp);
	if (argc != 2)
	{
		run_tests(&shell);
		t_minishell_free(&shell);
		return (0);
	}
	shell.input = ft_strdup(argv[1]);
	token_recognition(&shell);
	tokens = shell.tokens;
	token = tokens->content;
	while (token->type != END)
	{
		print_token((void *)tokens->content);
		result = expand_string(&token->str, &shell, O_PATH | O_VAR | O_QUOTE);
		if (result == NULL)
			printf("ERROR");
		ft_lstprint(result, print_str);
		ft_lstclear(&result, free);
		tokens = tokens->next;
		token = tokens->content;
		printf("\n\n");
	}
	ft_lstclear(&shell.tokens, t_token_free);
	t_minishell_free(&shell);
	return (0);
}
