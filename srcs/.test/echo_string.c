/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:11:36 by brappo            #+#    #+#             */
/*   Updated: 2024/04/18 17:14:50 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

void	echo_string(char *str, char **envp, char *result_perso)
{
	pid_t	pid;
	int		tube_to_process[2];
	int		tube_from_process[2];
	char	*argv[2];
	char	buffer[2048];
	int		rd;

	argv[0] = "/usr/bin/bash";
	argv[1] = NULL;
	pipe(tube_to_process);
	pipe(tube_from_process);
	write(tube_to_process[1], "echo ", 5);
	write(tube_to_process[1], str, ft_strlen(str));
	close(tube_to_process[1]);
	pid = fork();
	if (pid == 0)
	{
		dup2(tube_to_process[0], STDIN_FILENO);
		close(tube_to_process[0]);
		dup2(tube_from_process[1], STDOUT_FILENO);
		close(tube_from_process[0]);
		close(tube_from_process[1]);
		execve(argv[0], argv, envp);

	}
	else
	{
		wait(NULL);
		close(tube_from_process[1]);
		rd = read(tube_from_process[0], buffer, 2048);
		buffer[rd] = '\0';
		if (rd > 0 && buffer[rd - 1] == '\n')
			buffer[rd - 1] = '\0';
		printf("bash : %s\n", buffer);
		if (string_equals((void *)buffer, (void *)result_perso))
			printf("equals ? : %strue%s\n",  GREEN, RESET);
		else
			printf("equals ? : %sfalse%s\n", RED, RESET);
	}
}
