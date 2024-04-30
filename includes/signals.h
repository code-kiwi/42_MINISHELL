/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:11:55 by root              #+#    #+#             */
/*   Updated: 2024/04/30 17:41:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

# define RL_ERROR "readline error"
# define INTERACTIVE -1
# define NON_INTERACTIVE -2

void	init_signals(void);
void	handle_interactive_signals(t_minishell *shell);
bool	catch_sigint(void);
void	set_interactive_mode(bool interactive);

#endif // !SIGNALS_H