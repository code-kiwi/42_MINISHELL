/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:11:55 by root              #+#    #+#             */
/*   Updated: 2024/04/30 14:23:15 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# define RL_ERROR "readline error"

# include "minishell.h"

void	init_signals(void);
void	handle_interactive_signals(t_minishell *shell);
bool	catch_sigint(void);

#endif // !SIGNALS_H