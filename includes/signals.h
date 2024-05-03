/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:11:55 by root              #+#    #+#             */
/*   Updated: 2024/05/03 12:16:10 by brappo           ###   ########.fr       */
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
int		stop_readline(void);
bool	interrupted(char *input);

#endif // !SIGNALS_H