/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:11:55 by root              #+#    #+#             */
/*   Updated: 2024/05/01 10:32:02 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

# define RL_ERROR "readline error"
# define KILL_ERROR "kill error"
# define SIGNAL_ERROR "Error in signals"
# define INTERACTIVE -1
# define NON_INTERACTIVE -2
# define ERROR_SIGNAL -3

bool	catch_sigint(void);
void	set_interactive_mode(bool interactive);
bool	get_sigint(void);
void	signal_handler(int code);
bool	get_signal_error(void);

#endif // !SIGNALS_H