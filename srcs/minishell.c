/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:14:16 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/28 11:40:26 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(void)
// {
// 	t_minishell	shell;

// 	t_minishell_init(&shell);
// 	while (true)
// 	{
// 		shell.input = prompt();
// 		if (shell.input == NULL)
// 			handle_error(&shell, ERROR_MSG_PROMPT, EXIT_FAILURE);
// 		if (ft_strcmp(shell.input, "exit") == 0)
// 		{
// 			t_minishell_free(&shell);
// 			break ;
// 		}
// 		printf("%s\n", shell.input);
// 		free(shell.input);
// 		shell.input = NULL;
// 	}
// 	exit(EXIT_SUCCESS);
// }

void	set_tests(char **tests)
{
	tests[0] = "";
	tests[1] = "echo";
	tests[2] = "t";
	tests[3] = "qwieuhqiuwhxeiuqhwiuexhquihwexiquhwex";
	tests[4] = "echo 7 || ls -la && echo 3";
	tests[5] = "e r x t l o i k";
	tests[6] = "echo ";
	tests[7] = "echo       ";
	tests[8] = " echo";
	tests[9] = "      echo";
	tests[10] = "echo<<";
	tests[11] = "echo <<";
	tests[12] = "<<echo";
	tests[13] = "<< echo";
	tests[14] = "echo >>>>>";
	tests[15] = ">>";
	tests[16] = "echo\"test\"";
	tests[17] = "echo \"test\"";
	tests[18] = "echo \"      \"";
	tests[19] = "\"\"";
	tests[20] = "\"qwxeq\"";
	tests[16] = "echo\'test\'";
	tests[17] = "echo \'test\'";
	tests[18] = "echo \'      \'";
	tests[19] = "\'\'";
	tests[20] = "\'qwxeq\'";
	tests[21] = "ls -la | echo test | echo truc";
	tests[22] = "echo'test";
	tests[23] = "echo\"test";
	tests[24] = "echo'<<'";
	tests[25] = "echo\"<<\"<\"<\"";
	tests[26] = "echo'<<'<<";
	tests[27] = ">>>";
	tests[28] = ">>>>";
	tests[29] = ">>>>>";
	tests[30] = "&||";
	tests[31] = "&&||";
	tests[32] = "&&|";
	tests[33] = "echo&&||>>>test";
}

int	main(void)
{
	char	*tests[34];
	size_t	index;
	t_list	*tokens;
	char	*dup_str;

	index = 0;
	set_tests(tests);
	while (index < 34)
	{
		printf("\033[0;32m");
		printf("\n%s\n", tests[index]);
		printf("\033[0m");
		dup_str = ft_strdup(tests[index]);
		if (dup_str == NULL)
			return (1);
		tokens = token_recognition(dup_str);
		print_list(tokens);
		ft_lstclear(&tokens, t_token_free);
		free(dup_str);
		index++;
	}
	return (0);
}
