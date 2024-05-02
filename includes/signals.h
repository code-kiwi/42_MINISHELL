/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:11:55 by root              #+#    #+#             */
/*   Updated: 2024/05/02 09:06:31 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"
# include "stdio.h"

# define RL_ERROR "readline error"
# define KILL_ERROR "kill error"
# define INTERACTIVE -1
# define NON_INTERACTIVE -2

bool	catch_sigint(void);
void	set_interactive_mode(bool interactive);
bool	get_sigint(void);
void	signal_handler(int code);
int		ft_getc(FILE *stream);

#endif // !SIGNALS_H