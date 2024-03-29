/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:54:36 by brappo            #+#    #+#             */
/*   Updated: 2024/03/29 13:17:48 by brappo           ###   ########.fr       */
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

	reset_len = ft_strlen(RESET);
	input_len = ft_strlen(start_color);
	color_len = ft_strlen(color);
	if (input_len + color_len + reset_len > buffer_size)
		return ;
	reset_index = start_color + end_color + color_len;
	ft_memmove(reset_index + reset_len, start_color + end_color,
		input_len - end_color + 1);
	ft_memcpy(reset_index, RESET, reset_len);
	ft_memmove(start_color + color_len, start_color, end_color);
	ft_memcpy(start_color, color, color_len);
}

void	add_current_user(char *cwd)
{
	char	*username;
	size_t	username_length;

	username = getenv("USER");
	if (username == NULL)
		return ;
	username_length = ft_strlen(username);
	ft_memmove(cwd + username_length, cwd, CWD_BUFFER_SIZE);
	ft_memcpy(cwd, username, username_length);
	set_color(cwd, username_length, GREEN, CWD_BUFFER_SIZE);
}

void	replace_home_by_tidle(char *cwd)
{
	char	*home_directory;
	char	*home_in_cwd;

	home_directory = getenv("HOME");
	if (home_directory == NULL)
		return ;
	home_in_cwd = ft_strstr(cwd, home_directory);
	if (home_in_cwd == NULL)
		return ;
	ft_memmove(cwd + 1, home_in_cwd + ft_strlen(home_directory),
		CWD_BUFFER_SIZE);
	cwd[0] = '~';
	set_color(cwd, ft_strlen(cwd) - 1 - 1, BLUE, CWD_BUFFER_SIZE);
}

void	get_directory_path(char *buffer, t_minishell *shell)
{
	size_t	cwd_length;

	if (getcwd(buffer, CWD_BUFFER_SIZE - 2) == NULL)
	{
		handle_error(shell, ERROR_CWD, EXIT_FAILURE);
		if (errno == ERANGE)
			handle_error(shell, ERROR_BUFFER, EXIT_FAILURE);
	}
	cwd_length = ft_strlen(buffer);
	buffer[cwd_length] = '$';
	buffer[cwd_length + 1] = ' ';
	buffer[cwd_length + 2] = '\0';
	replace_home_by_tidle(buffer);
	add_current_user(buffer);
}
