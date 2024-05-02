/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:09:18 by brappo            #+#    #+#             */
/*   Updated: 2024/05/02 16:39:32 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <stdlib.h>

# define CWD_BUFFER_SIZE	2048
# define RESET				"\001\033[0m\002"
# define GREEN				"\001\033[32m\002"
# define BLUE				"\001\033[34m\002"
# define RED				"\001\033[31m\002"

typedef struct s_minishell	t_minishell;

// Prompt functions
bool	get_directory_path(char *buffer, size_t buffer_size);
char	*prompt(t_minishell *shell);

#endif
