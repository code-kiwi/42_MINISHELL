/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_heredoc_exec_info_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:06:23 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/10 16:58:02 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "execution.h"

/*
 *	Sets the given hdc_info's error flag to true
 */
void	hdc_info_set_error(t_heredoc_exec_info *hdc_info)
{
	if (hdc_info == NULL)
		return ;
	hdc_info->error_flag = true;
}

/*
 *	Sets the given hdc_info's interruption flag to true
 */
void	hdc_info_set_interruption(t_heredoc_exec_info *hdc_info)
{
	if (hdc_info == NULL)
		return ;
	hdc_info->interruption = true;
}
