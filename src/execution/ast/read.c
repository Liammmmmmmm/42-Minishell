/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:37:35 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/25 14:30:24 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	recursive_tree_read(t_minishell *minishell, t_ast_node *node)
{
	if (!node)
		return (0);
	if (node->cmd_res == -2)
	{
		if (node->token == COMMAND)
			exec_cmd(node, minishell);
		if (node->child_left)
			recursive_tree_read(minishell, node->child_left);
	}
	return -1;
}

void	execute_ast(t_minishell *minishell)
{
	printf("ok %d, %s\n", minishell->ast_root->token, minishell->ast_root->text);
	recursive_tree_read(minishell, minishell->ast_root);
}
