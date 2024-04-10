/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brappo <brappo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:37:10 by brappo            #+#    #+#             */
/*   Updated: 2024/04/10 10:38:05 by brappo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILD_AST_H
# define BUILD_AST_H
# include "minishell.h"


bool	set_operator_type(t_list *tokens);

#endif // !BUILD_AST_H