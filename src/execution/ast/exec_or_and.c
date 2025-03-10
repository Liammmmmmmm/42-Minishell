/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:39:50 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/10 12:19:46 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_and_or(t_minishell *minishell, t_ast_node *node, int is_and)
{
	int	status;

	status = recursive_tree_read(minishell, node->child_left);
	if (is_and && status != 0)
		return (status);
	if (!is_and && status == 0)
		return (status);
	status = recursive_tree_read(minishell, node->child_right);
	return (status);
}
