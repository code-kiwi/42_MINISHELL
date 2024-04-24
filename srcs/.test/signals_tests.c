/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_tests.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:17:08 by brappo            #+#    #+#             */
/*   Updated: 2024/04/20 10:39:03 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signals(int code)
{
	static int	count = 0;

	printf("code received : %d\n", code);
	count++;
	if (count == 3)
		exit(EXIT_SUCCESS);
}

int	main(void)
{
	size_t	seconds;

	seconds = 0;
	signal(SIGINT, &handle_signals);
	while (true)
	{
		printf("seconds : %ld\n", seconds);
		sleep(1);
		seconds++;
	}
	printf("test");
	return (0);
}