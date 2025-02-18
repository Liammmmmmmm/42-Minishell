/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:31:18 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/18 15:10:37 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

#include "tokens.h"

typedef struct s_ast_node	t_ast_node;

typedef struct s_ast_node
{
	t_token_type	token;
	char			*text;
	t_ast_node		*parent;
	t_ast_node		*child_left;
	t_ast_node		*child_right;
	
}	t_ast_node;

#endif
