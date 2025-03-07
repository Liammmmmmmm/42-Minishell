/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:37:35 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/06 12:33:30 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	recursive_tree_read(t_minishell *minishell, t_ast_node *node)
{
	if (!node)
		return (1);
	else if (node->token == COMMAND)
		return (exec_cmd(node, minishell));
	else if (node->token == REDIRECT_IN || node->token == REDIRECT_OUT
		|| node->token == REDIRECT_OUT_APPEND || node->token == HERE_DOC)
		return (exec_redirect(minishell, node));
	else if (node->token == OR)
		return (exec_and_or(minishell, node, 0));
	else if (node->token == AND)
		return (exec_and_or(minishell, node, 1));
	else if (node->token == PIPE)
		return (exec_pipe(minishell, node));
	return (1);
}

void	execute_ast(t_minishell *minishell)
{
	int		status;

	// printf("ok %d, %s\n", minishell->ast_root->token, minishell->ast_root->text);
	// deja faire une premiere fork ici dans tous les cas pour eviter d'avoir des pb genre si on a que une seule commande ici je peux mettre des <3 !!
	
	status = recursive_tree_read(minishell, minishell->ast_root);
	minishell->last_res = status;
}