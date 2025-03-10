/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   low_tree_func_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:44:04 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/10 13:44:25 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*go_up_tree(t_ast_node *tree)
{
	if (tree == NULL)
		return (NULL);
	if (tree->parent == NULL)
		return (tree);
	else
		return (go_up_tree(tree->parent));
}

void	free_tree_rec(t_ast_node *tree)
{
	if (tree != NULL)
	{
		free_tree_rec(tree->child_left);
		free_tree_rec(tree->child_right);
		free(tree);
	}
}

void	free_tree(t_minishell *minishell)
{
	free_tree_rec(go_up_tree(minishell->ast_root));
	minishell->ast_root = NULL;
}