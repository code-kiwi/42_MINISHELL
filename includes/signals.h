/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:11:55 by root              #+#    #+#             */
/*   Updated: 2024/04/30 14:01:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGANLS_H

# define RL_ERROR "readline error"

# include "minishell.h"

void	init_signals();
void	handle_interactive_signals(t_minishell *shell);
bool	catch_sigint();

#endif // !SIGNALS_H