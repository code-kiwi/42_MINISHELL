/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:54:36 by brappo            #+#    #+#             */
/*   Updated: 2024/03/28 13:51:57 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_current_user(char *cwd)
{
	char	*username;
	size_t	username_length;
	size_t	index;

	username = getenv("USER");
	if (username == NULL)
		return ;
	username_length = ft_strlen(username);
	index = 0;
	ft_memmove(cwd + username_length, cwd, CWD_BUFFER_SIZE);
	while (index < username_length)
	{
		cwd[index] = username[index];
		index++;
	}
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
	ft_memmove(cwd + 1, home_in_cwd + ft_strlen(home_directory), CWD_BUFFER_SIZE);
	cwd[0] = '~';
}

void	get_directory_path(char *buffer, t_minishell *shell)
{
	size_t	cwd_length;

	if (getcwd(buffer, CWD_BUFFER_SIZE - 1) == NULL)
	{
		handle_error(shell, ERROR_CWD, EXIT_FAILURE);
		if (errno == ERANGE)
			handle_error(shell, ERROR_BUFFER, EXIT_FAILURE);
	}
	cwd_length = ft_strlen(buffer);
	buffer[cwd_length] = '$';
	buffer[cwd_length + 1] = '\0';	
	replace_home_by_tidle(buffer);
	add_current_user(buffer);
}
