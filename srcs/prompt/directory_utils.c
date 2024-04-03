/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:54:36 by brappo            #+#    #+#             */
/*   Updated: 2024/04/03 16:35:00 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_color(char *start_color, size_t end_color,
		char *color, size_t buffer_size)
{
	size_t	color_len;
	size_t	input_len;
	char	*reset_index;
	size_t	reset_len;

	if (buffer_size == 0)
		return ;
	reset_len = ft_strlen(RESET);
	input_len = ft_strlen(start_color);
	color_len = ft_strlen(color);
	if (end_color > buffer_size || end_color > input_len)
		return ;
	if (input_len + color_len + reset_len + 1 > buffer_size)
		return ;
	reset_index = start_color + end_color + color_len;
	ft_memmove(reset_index + reset_len, start_color + end_color,
		input_len - end_color + 1);
	ft_memcpy(reset_index, RESET, reset_len);
	ft_memmove(start_color + color_len, start_color, end_color);
	ft_memcpy(start_color, color, color_len);
}

void	add_current_user(char *cwd, size_t buffer_size, bool add_color)
{
	char	*username;
	size_t	username_length;

	username = getenv("USER");
	if (username == NULL)
		return ;
	username_length = ft_strlen(username);
	if (ft_strlen(cwd) + username_length + 1 >= buffer_size)
		return ;
	ft_memmove(cwd + username_length, cwd, ft_strlen(cwd) + 1);
	ft_memcpy(cwd, username, username_length);
	if (add_color)
		set_color(cwd, username_length, GREEN, buffer_size);
}

void	replace_home_by_tidle(char *cwd, size_t buffer_size, bool add_color)
{
	char	*home_directory;
	size_t	home_directory_length;
	char	*home_directory_in_cwd;
	size_t	cwd_length;

	home_directory = getenv("HOME");
	if (home_directory == NULL)
		return ;
	home_directory_in_cwd = ft_strstr(cwd, home_directory);
	cwd_length = ft_strlen(cwd);
	home_directory_length = ft_strlen(home_directory);
	if (home_directory_in_cwd != cwd
		|| (cwd[home_directory_length] != '/' && cwd[home_directory_length]))
		return ;
	if (cwd_length + 2 > buffer_size)
		return ;
	ft_memmove(cwd + 1, cwd + home_directory_length,
		cwd_length - home_directory_length + 1);
	cwd[0] = '~';
	if (add_color)
		set_color(cwd + 1, cwd_length - home_directory_length - 1,
			BLUE, buffer_size);
}

void	get_directory_path(char *buffer, t_minishell *shell, size_t buffer_size)
{
	size_t	cwd_length;
	bool	add_color;

	if (getcwd(buffer, buffer_size - 2) == NULL)
	{
		handle_error(shell, ERROR_CWD, EXIT_FAILURE);
		if (errno == ERANGE)
			handle_error(shell, ERROR_BUFFER, EXIT_FAILURE);
	}
	cwd_length = ft_strlen(buffer);
	buffer[cwd_length] = '$';
	buffer[cwd_length + 1] = ' ';
	buffer[cwd_length + 2] = '\0';
	add_color = getenv("TERM") != NULL && isatty(1);
	replace_home_by_tidle(buffer, buffer_size, add_color);
	add_current_user(buffer, buffer_size, add_color);
}
