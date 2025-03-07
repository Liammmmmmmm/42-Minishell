/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:57:57 by agantaum          #+#    #+#             */
/*   Updated: 2025/03/06 15:06:17 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_part	*manage_open(t_ast_node *tree, t_cmd_part *cmd, int *flag)
{
	t_ast_node	*tree2;

	tree2 = new_node();
	if (tree2 == NULL)
		return (flag_off(flag));
	cmd = fill_tree(tree2, cmd->next, 0);
	if (tree2 == NULL || cmd == NULL)
		return (flag_off(flag));
	tree2 = go_up_tree(tree2);
	if (tree2->token == NULL_TOKEN)
	{
		tree2 = tree2->child_left;
		free(tree2->parent);
	}
	cpy_node(tree, tree2);
	free(tree2);
	if (check_parent(tree) == 0)
		return (flag_off(flag));
	return (fill_tree(tree->parent, cmd->next, flag));
}

t_cmd_part	*manage_nnode(t_ast_node *tree, t_cmd_part *cmd, int *flag)
{
	if (cmd->token == PAREN_OPEN)
		return (manage_open(tree, cmd, flag));
	else if (cmd->token == PIPE || cmd->token == OR || cmd->token == AND)
		tree->token = cmd->token;
	else if (cmd->token == COMMAND)
	{
		tree->token = cmd->token;
		tree->text = cmd->text;
	}
	else if (cmd->token == REDIRECT_IN || cmd->token == HERE_DOC
		|| cmd->token == REDIRECT_OUT || cmd->token == REDIRECT_OUT_APPEND)
	{
		tree->token = cmd->token;
		tree->text = cmd->next->text;
		return (fill_tree(tree, cmd->next->next, flag));
	}
	return (fill_tree(tree, cmd->next, flag));
}

t_cmd_part	*manage_redirect(t_ast_node *tree, t_cmd_part *cmd, int *flag)
{
	t_ast_node	*n_node;

	if (cmd->token == REDIRECT_IN || cmd->token == HERE_DOC
		|| cmd->token == REDIRECT_OUT || cmd->token == REDIRECT_OUT_APPEND)
	{
		n_node = new_node();
		if (n_node == NULL)
			return (flag_off(flag));
		if (tree->child_left == NULL)
		{
			n_node = new_node();
			if (n_node == NULL)
				return (flag_off(flag));
			n_node->parent = tree;
			tree->child_left = n_node;
		}
		n_node->parent = tree;
		n_node->child_left = tree->child_left;
		tree->child_left->parent = n_node;
		tree->child_left = n_node;
		return (fill_tree(tree->child_left, cmd, flag));
	}
	if (check_parent(tree) == 0)
		return (flag_off(flag));
	return (fill_tree(tree->parent, cmd, flag));
}

t_cmd_part	*manage_pipe(t_ast_node *tree, t_cmd_part *cmd, int *flag)
{
	t_ast_node	*n_node;

	if (tree->child_right == NULL)
	{
		n_node = new_node();
		if (n_node == NULL)
			return (flag_off(flag));
		n_node->parent = tree;
		tree->child_right = n_node;
		return (fill_tree(tree->child_right, cmd, flag));
	}
	if (cmd->token == REDIRECT_IN || cmd->token == HERE_DOC
		|| cmd->token == REDIRECT_OUT || cmd->token == REDIRECT_OUT_APPEND)
	{
		n_node = new_node();
		if (n_node == NULL)
			return (flag_off(flag));
		insert_node(tree, n_node);
		return (fill_tree(tree->child_right, cmd, flag));
	}
	if (check_parent(tree) == 0)
		return (flag_off(flag));
	return (fill_tree(tree->parent, cmd, flag));
}

t_cmd_part	*manage_orand(t_ast_node *tree, t_cmd_part *cmd, int *flag)
{
	t_ast_node	*n_node;

	if (tree->child_right == NULL)
	{
		n_node = new_node();
		if (n_node == NULL)
			return (flag_off(flag));
		n_node->parent = tree;
		tree->child_right = n_node;
		return (fill_tree(tree->child_right, cmd, flag));
	}
	if (cmd->token == PIPE || cmd->token == REDIRECT_IN
		|| cmd->token == HERE_DOC
		|| cmd->token == REDIRECT_OUT || cmd->token == REDIRECT_OUT_APPEND)
	{
		n_node = new_node();
		if (n_node == NULL)
			return (flag_off(flag));
		insert_node(tree, n_node);
		return (fill_tree(tree->child_right, cmd, flag));
	}
	if (check_parent(tree) == 0)
		return (flag_off(flag));
	return (fill_tree(tree->parent, cmd, flag));
}
