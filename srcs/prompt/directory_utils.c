/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:54:36 by brappo            #+#    #+#             */
/*   Updated: 2024/05/15 09:30:25 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include "libft.h"
#include "minishell.h"
#include "prompt.h"
#include "env.h"

static void	set_color(char *start_color, size_t end_color,
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

static void	add_current_user(
	t_list *env, char *cwd, size_t buffer_size, bool add_color
)
{
	char	*username;
	size_t	username_length;

	username = env_get(env, ENV_USER);
	if (username == NULL)
		return ;
	username_length = ft_strlen(username);
	if (ft_strlen(cwd) + username_length + 1 >= buffer_size)
	{
		free(username);
		return ;
	}
	ft_memmove(cwd + username_length, cwd, ft_strlen(cwd) + 1);
	ft_memcpy(cwd, username, username_length);
	free(username);
	if (add_color)
		set_color(cwd, username_length, GREEN, buffer_size);
}

static bool	replace_home_by_tilde(
	t_list *env, char *cwd, size_t buffer_size
)
{
	char	*home_directory;
	size_t	home_directory_length;
	char	*home_directory_in_cwd;
	size_t	cwd_length;

	home_directory = env_get(env, ENV_HOME);
	if (home_directory == NULL)
		return (false);
	home_directory_in_cwd = ft_strstr(cwd, home_directory);
	cwd_length = ft_strlen(cwd);
	home_directory_length = ft_strlen(home_directory);
	free(home_directory);
	if (home_directory_in_cwd != cwd
		|| (cwd[home_directory_length] != '/' && cwd[home_directory_length]))
		return (false);
	if (cwd_length + 2 > buffer_size)
		return (false);
	ft_memmove(cwd + 1, cwd + home_directory_length,
		cwd_length - home_directory_length + 1);
	cwd[0] = '~';
	return (true);
}

bool	get_directory_path(t_list *env, char *buffer, size_t buffer_size)
{
	size_t	cwd_length;
	bool	add_color;

	if (getcwd(buffer, buffer_size - 2) == NULL)
		return (false);
	cwd_length = ft_strlen(buffer);
	buffer[cwd_length] = '$';
	buffer[cwd_length + 1] = ' ';
	buffer[cwd_length + 2] = '\0';
	add_color = env_exists(env, ENV_TERM) && isatty(STDOUT_FILENO);
	if (replace_home_by_tilde(env, buffer, buffer_size) && add_color)
		set_color(buffer + 1, ft_strlen(buffer) - 3, BLUE, buffer_size);
	else if (add_color)
		set_color(buffer, ft_strlen(buffer) - 2, BLUE, buffer_size);
	add_current_user(env, buffer, buffer_size, add_color);
	return (true);
}
