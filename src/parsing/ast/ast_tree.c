/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:30:28 by agantaum          #+#    #+#             */
/*   Updated: 2025/02/24 09:51:18 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int fill_tree(t_ast_node  *tree, t_cmd_part *cmd, int depth)
{
	t_ast_node  *n_node;
	if (cmd == NULL)
		return (1);
	if (tree->token == NULL_TOKEN)
	{
		if (cmd->token == PIPE || cmd->token == OR || cmd->token == AND)
			tree->token = cmd->token;
		if (cmd->token == COMMAND)
		{
			tree->token = cmd->token;
			tree->text = cmd->text;
		}
		if (cmd->token == REDIRECT_IN || cmd->token == REDIRECT_OUT || cmd->token == REDIRECT_OUT_APPEND)
		{
			tree->token = cmd->token;
			tree->text = cmd->next->text;
			return (fill_tree(tree, cmd->next->next, depth));
		}
		return (fill_tree(tree, cmd->next, depth));
	}
	if (tree->token == COMMAND)
	{
		if (tree->parent == NULL)
		{
			n_node = new_node();
			if (n_node == NULL)
				return (1);
			n_node->child_left = tree;
			tree->parent = n_node;
		}
		return (fill_tree(tree->parent, cmd, depth));
	}
	if (tree->token == REDIRECT_IN || tree->token == REDIRECT_OUT || tree->token == REDIRECT_OUT_APPEND)
	{
		if (cmd->token == REDIRECT_IN || cmd->token == REDIRECT_OUT || cmd->token == REDIRECT_OUT_APPEND)
		{
			n_node = new_node();
			if (n_node == NULL)
				return (1);
			n_node->parent = tree;
			n_node->child_left = tree->child_left;
			tree->child_left->parent = n_node;
			tree->child_left = n_node;
			return (fill_tree(tree->child_left, cmd, depth));
		}
		if (tree->parent == NULL)
		{
			n_node = new_node();
			if (n_node == NULL)
				return (1);
			n_node->child_left = tree;
			tree->parent = n_node;
		}
		return (fill_tree(tree->parent, cmd, depth));
	}
	if (tree->token == PIPE)
	{
		if (tree->child_right == NULL)
		{
			n_node = new_node();
			if (n_node == NULL)
				return (1);
			n_node->parent = tree;
			tree->child_right = n_node;
			return (fill_tree(tree->child_right, cmd, depth));
		}
		if (cmd->token == REDIRECT_IN || cmd->token == REDIRECT_OUT || cmd->token == REDIRECT_OUT_APPEND)
		{
			n_node = new_node();
			if (n_node == NULL)
				return (1);
			n_node->parent = tree;
			n_node->child_left = tree->child_right;
			tree->child_right->parent = n_node;
			tree->child_right = n_node;
			return (fill_tree(tree->child_right, cmd, depth));
		}
		if (tree->parent == NULL)
		{
			n_node = new_node();
			if (n_node == NULL)
				return (1);
			n_node->child_left = tree;
			tree->parent = n_node;
		}
		return (fill_tree(tree->parent, cmd, depth));
	}
	if (tree->token == OR || tree->token == AND)
	{
		if (tree->child_right == NULL)
		{
			n_node = new_node();
			if (n_node == NULL)
				return (1);
			n_node->parent = tree;
			tree->child_right = n_node;
			return (fill_tree(tree->child_right, cmd, depth));
		}
		if (cmd->token == PIPE || cmd->token == REDIRECT_IN || cmd->token == REDIRECT_OUT || cmd->token == REDIRECT_OUT_APPEND)
		{
			n_node = new_node();
			if (n_node == NULL)
				return (1);
			n_node->parent = tree;
			n_node->child_left = tree->child_right;
			tree->child_right->parent = n_node;
			tree->child_right = n_node;
			return (fill_tree(tree->child_right, cmd, depth));
		}
		if (tree->parent == NULL)
		{
			n_node = new_node();
			if (n_node == NULL)
				return (1);
			n_node->child_left = tree;
			tree->parent = n_node;
		}
		return (fill_tree(tree->parent, cmd, depth));
	}
	return (1);
}

int cmd_to_tree(t_cmd_part *cmd)
{
    t_ast_node *tree;
    
    tree = new_node();
    if (tree == NULL)
        return (-1);
    fill_tree(tree, cmd, 0);
    ft_printf("--------------\n");
    printf_tree(tree, -1);
    ft_printf("--------------\n");
    free_tree(tree);
    return (1);
}