/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:31:18 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/06 12:03:51 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "tokens.h"
# include "tokenization.h"

typedef struct s_ast_node	t_ast_node;

typedef struct s_ast_node
{
	t_token_type	token;
	char			*text;
	t_ast_node		*parent;
	t_ast_node		*child_left;
	t_ast_node		*child_right;
	int				cmd_res;
	pid_t			pid;
}	t_ast_node;

void		*flag_off(int *flag);

char		*null_or_txt(char *str);

int			check_parent(t_ast_node *tree);

void		printf_tree(t_ast_node *tree, int niveau);
void		cpy_node(t_ast_node *tree, t_ast_node *tree2);
void		insert_node(t_ast_node *tree, t_ast_node *n_node);

t_ast_node	*new_node(void);
t_ast_node	*go_up_tree(t_ast_node *tree);

t_cmd_part	*fill_tree(t_ast_node *tree, t_cmd_part *cmd, int *flag);
t_cmd_part	*manage_pipe(t_ast_node *tree, t_cmd_part *cmd, int *flag);
t_cmd_part	*manage_open(t_ast_node *tree, t_cmd_part *cmd, int *flag);
t_cmd_part	*manage_nnode(t_ast_node *tree, t_cmd_part *cmd, int *flag);
t_cmd_part	*manage_orand(t_ast_node *tree, t_cmd_part *cmd, int *flag);
t_cmd_part	*manage_redirect(t_ast_node *tree, t_cmd_part *cmd, int *flag);

#endif
