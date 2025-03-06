/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:39:50 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/06 12:52:23 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_and_or(t_minishell *minishell, t_ast_node *node, int is_and)
{
	int	status;
	
	status = recursive_tree_read(minishell, node->child_left);
	printf("STATUSSSS %d\n", status);
	if (is_and && status != 0)
		return (status);
	if (!is_and && status == 0)
		return (status);
	status = recursive_tree_read(minishell, node->child_right);
	return (status);
}

// int exec_and_or(t_minishell *minishell, t_ast_node *node, int is_and)
// {
// 	pid_t	pid;
// 	int		status;

// 	pid = fork();
// 	if (pid == -1)
// 		return (perror_ret(minishell));
// 	else if (pid == 0)
// 	{
// 		status = recursive_tree_read(minishell, node->child_left);
// 		free_exit(minishell, status);
// 	}
// 	status = 1;
// 	waitpid(pid, &status, 0);
// 	if (is_and && status != 0)
// 		free_exit(minishell, status);
// 	if (!is_and && status == 0)
// 		free_exit(minishell, status);
// 	status = recursive_tree_read(minishell, node->child_right);
// 	free_exit(minishell, status);
// 	return (1);
// }