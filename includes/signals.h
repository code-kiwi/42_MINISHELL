/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:11:55 by root              #+#    #+#             */
/*   Updated: 2024/05/13 13:54:25 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"
# include "stdio.h"

# define INTERACTIVE        -1
# define NON_INTERACTIVE    -2

void	set_interactive_mode(bool interactive);
bool	get_sigint(void);
void	signal_handler(int code);
int		stop_readline(void);
bool	interrupted(char *input);
bool	get_sigquit(void);

#endif
