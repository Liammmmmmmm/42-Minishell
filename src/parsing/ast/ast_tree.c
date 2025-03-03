/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:30:28 by agantaum          #+#    #+#             */
/*   Updated: 2025/03/03 11:21:06 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_part	*fill_tree(t_ast_node *tree, t_cmd_part *cmd, int *flag)
{
	if (cmd == NULL || cmd->token == PAREN_CLOSE)
		return (cmd);
	if (tree->token == NULL_TOKEN)
		return (manage_nnode(tree, cmd, flag));
	if (tree->token == COMMAND)
	{
		if (check_parent(tree) == 0)
			return (flag_off(flag));
		return (fill_tree(tree->parent, cmd, flag));
	}
	if (tree->token == REDIRECT_IN || cmd->token == HERE_DOC
		|| tree->token == REDIRECT_OUT || tree->token == REDIRECT_OUT_APPEND)
		return (manage_redirect(tree, cmd, flag));
	if (tree->token == PIPE)
		return (manage_pipe(tree, cmd, flag));
	if (tree->token == OR || tree->token == AND)
		return (manage_orand(tree, cmd, flag));
	return (cmd);
}

int	cmd_to_tree(t_cmd_part *cmd, t_minishell *minishell)
{
	t_ast_node	*tree;
	int			flag;

	flag = 1;
	tree = new_node();
	if (tree == NULL)
		return (-1);
	fill_tree(tree, cmd, &flag);
	if (flag == 0 || tree == NULL)
		return (-1);
	if (tree->parent != NULL && tree->parent->token == NULL_TOKEN)
	{
		free(tree->parent);
		tree->parent = NULL;
	}
	minishell->ast_root = tree;
	return (1);
}
