/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:09:18 by brappo            #+#    #+#             */
/*   Updated: 2024/04/03 14:05:27 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "minishell.h"
# define ERROR_MSG_PROMPT "Prompt function error"
# define ERROR_CWD "Cannot get current working directory path"
# define ERROR_BUFFER "Buffer size too small"
# define CWD_BUFFER_SIZE 2048
# define RESET "\033[0m"
# define GREEN "\033[32m"
# define BLUE "\033[34m"

// Prompt functions
void	get_directory_path(char *buffer, t_minishell *shell,
			size_t buffer_size);
char	*prompt(t_minishell *shell);

#endif

