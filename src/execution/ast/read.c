/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:37:35 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/03 16:32:24 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd_test(t_minishell *minishell, t_ast_node *node)
{
	(void)minishell;
	if (node != NULL && node->text[0] == 'o')
		return (0);
	return (1);
}

int	exec_redirect(t_minishell *minishell, t_ast_node *node)
{
	// quand on est la on est deja dans un child, on peut donc modifier les fd comme des porcs on s'en fou
	// 
	(void)minishell;
	if (node != NULL && node->text[0] == 'o')
		return (0);
	return (1);
}

int exec_and_or(t_minishell *minishell, t_ast_node *node, int is_and)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror_ret(minishell));
	else if (pid == 0)
	{
		status = recursive_tree_read(minishell, node->child_left);
		free_msh(minishell);
		exit(status);
	}
	status = 1;
	waitpid(pid, &status, 0);
	if (is_and && status != 0)
	{
		free_msh(minishell);
		exit(status);
	}
	if (!is_and && status == 0)
	{
		printf("La j'exit hehehehe je suis un connnnard\n");
		free_msh(minishell);
		exit(status);
	}
	pid = fork();
	if (pid == -1)
		return (perror_ret(minishell));
	else if (pid == 0)
	{
		status = recursive_tree_read(minishell, node->child_right);
		free_msh(minishell);
		printf("status2 -> %d\n", status);
		exit(status);
	}
	status = 1;
	waitpid(pid, &status, 0);
	printf("status -> %d\n", status);
	return (status);
}

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
	pid_t	pid;
	int		status;

	printf("ok %d, %s\n", minishell->ast_root->token, minishell->ast_root->text);
	// deja faire une premiere fork ici dans tous les cas pour eviter d'avoir des pb genre si on a que une seule commande ici je peux mettre des <3 !!
	
	
	pid = fork();
	if (pid == -1)
		return ((void)perror_ret(minishell));
	else if (pid == 0)
	{
		status = recursive_tree_read(minishell, minishell->ast_root);
		free_msh(minishell);
		exit(status);
	}
	status = 0;
	waitpid(pid, &status, 0);
	minishell->last_res = status;
}