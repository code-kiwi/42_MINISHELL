/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:34:15 by brappo            #+#    #+#             */
/*   Updated: 2024/03/29 19:34:16 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_color(char *start_color, size_t end_color,
		char *color, size_t buffer_size);
void	add_current_user(char *cwd, size_t buffer_size);
void	replace_home_by_tidle(char *cwd, size_t buffer_size);

void	test_color(char *str, size_t start, size_t end, size_t buffer_size, char *color)
{
	char	*buffer;
	size_t	length;

	printf("(%s, %lu, %lu, %lu, color)\n", str, start,end, buffer_size);
	length = ft_strlen(str);
	buffer = (char *)malloc(buffer_size * sizeof(char));
	if (buffer == NULL)
		return ;
	if (length + 1 <= buffer_size)
		ft_memcpy(buffer, str, length + 1);
	set_color(buffer + start, end, color, buffer_size);
	if (length + 1 <= buffer_size)
		printf("%s", buffer);
	printf("\n\n");
	free(buffer);
}

void	test_add_username(char *input, size_t buffer_size)
{
	char	*buffer;
	size_t	length;

	length = ft_strlen(input);
	if (length >= buffer_size)
		return ;
	buffer = (char *)malloc(buffer_size * sizeof(char));
	if (buffer == NULL)
		return ;
	ft_memcpy(buffer, input, length + 1);
	add_current_user(buffer, buffer_size);
	printf("(%s, %lu)\n", input, buffer_size);
	printf("%s\n\n", buffer);
	free(buffer);
}

void	test_add_path(char *input, size_t buffer_size)
{
	char	*buffer;
	size_t	length;

	length = ft_strlen(input);
	if (length >= buffer_size)
		return ;
	buffer = (char *)malloc(buffer_size * sizeof(char));
	if (buffer == NULL)
		return ;
	ft_memcpy(buffer, input, length + 1);
	replace_home_by_tidle(buffer, buffer_size);
	printf("(%s, %lu)\n", input, buffer_size);
	printf("%s\n\n", buffer);
	free(buffer);
}

void	run_color_tests(void)
{
	printf("(char *str, size_t start, size_t end, size_t buffer_size, char *color)\n");
	test_color("premier", 0, ft_strlen("premier"), 24, BLUE);
	test_color("", 0, 0, 24, BLUE);
	test_color("", 0, 0, 1, BLUE);
	test_color("azexazxe", 0, ft_strlen("azwazxe"), 0, BLUE);
	test_color("test", 0, 4, 6, BLUE);
	test_color("test", 0, 4, 14, BLUE);
	test_color("test", 0, 4, 13, BLUE);
	test_color("je suis un test pour la couleur", 3, 4, 100, GREEN);
	test_color("je suis un test pour la couleur", 3, 100, 100, GREEN);
	test_color("je suis un test pour la couleur", 3, 103, 100, GREEN);
	test_color("je suis un test pour la couleur", 3, 120, 100, GREEN);
	test_color("je suis un test pour la couleur", 3, 99, 100, GREEN);
	test_color("t", 0, 1, 100, GREEN);
	test_color("t", 0, 2, 3, GREEN);
}

void	run_add_username_tests(void)
{
	// buffer_size ne peut pas être inférieur à la string car il contient la string
	printf("(char *input, size_t buffer_size)\n\n");
	test_add_username("je suis un test", 23);
	test_add_username("je suis un test", 22);
	test_add_username("je suis un test", 30);
	test_add_username("je suis un test", 100);
	test_add_username("", 10);
	test_add_username("", 5);
}

void	run_add_path_tests(void)
{
	// meme raison
	printf("(char *input, size_t buffer_size)\n");
	test_add_path("je suis un test", 23);
	test_add_path("/home/brappo/Documents", 22);
	test_add_path("/home/brappo", 30);
	test_add_path("/home/brappo/", 100);
	test_add_path("/home/brappotests", 100);
	test_add_path("", 100);
	test_add_path("", 5);
	test_add_path("home/brappo", 22);
}

int	main(void)
{
	run_color_tests();
	run_add_username_tests();
	run_add_path_tests();
}