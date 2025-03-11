/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   low_tree_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:33:53 by agantaum          #+#    #+#             */
/*   Updated: 2025/03/11 10:59:41 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*new_node(void)
{
	t_ast_node	*tree;

	tree = malloc(sizeof(t_ast_node));
	if (tree == NULL)
		return (NULL);
	tree->child_left = NULL;
	tree->child_right = NULL;
	tree->parent = NULL;
	tree->text = NULL;
	tree->token = NULL_TOKEN;
	tree->cmd_res = -2;
	tree->pid = -1;
	return (tree);
}

char	*null_or_txt(char *str)
{
	if (str == NULL)
		return ("(nil)");
	else
		return (str);
}
