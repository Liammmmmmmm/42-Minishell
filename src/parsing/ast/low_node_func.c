/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   low_node_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:06:42 by agantaum          #+#    #+#             */
/*   Updated: 2025/02/26 18:16:07 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*flag_off(int *flag)
{
	*flag = 0;
	return (NULL);
}

void	cpy_node(t_ast_node *tree, t_ast_node *tree2)
{
	tree->child_left = tree2->child_left;
	tree->child_right = tree2->child_right;
	tree->token = tree2->token;
	tree->text = tree2->text;
}

void	insert_node(t_ast_node *tree, t_ast_node *n_node)
{
	n_node->parent = tree;
	n_node->child_left = tree->child_right;
	tree->child_right->parent = n_node;
	tree->child_right = n_node;
}

int	check_parent(t_ast_node *tree)
{
	t_ast_node	*n_node;

	if (tree->parent == NULL)
	{
		n_node = new_node();
		if (n_node == NULL)
			return (0);
		n_node->child_left = tree;
		tree->parent = n_node;
	}
	return (1);
}
