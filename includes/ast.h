/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:31:18 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/21 14:35:57 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

#include "tokens.h"
#include "tokenization.h"

typedef struct s_ast_node	t_ast_node;

typedef struct s_ast_node
{
	t_token_type	token;
	char			*text;
	t_ast_node		*parent;
	t_ast_node		*child_left;
	t_ast_node		*child_right;
	
}	t_ast_node;

t_ast_node  *new_node(void);
t_ast_node  *new_tkn_node(t_token_type	token);

void printf_tree(t_ast_node *tree, int niveau);
void	free_tree(t_ast_node *tree);

int cmd_to_tree(t_cmd_part *cmd);
int fill_tree(t_ast_node  *tree, t_cmd_part *cmd, int depth);

char *null_or_txt(char *str);

#endif
