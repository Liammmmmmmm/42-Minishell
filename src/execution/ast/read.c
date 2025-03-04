/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:37:35 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/04 10:11:26 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_redirect(t_minishell *minishell, t_ast_node *node)
{
	int	fd;

	if (node->text)
	{
		if (node->token == REDIRECT_IN)
		{
			fd = open(node->text, O_RDONLY);
			if (fd == -1)
				perror_file(minishell, node->text);
			else
			{
				dup2(fd, STDIN_FILENO);
				if (close(fd) == -1)
					perror_ret(minishell);
			}
		}
		else if (node->token == HERE_DOC)
		{
			fd = open(node->text, O_RDONLY);
			if (fd == -1)
				perror_file(minishell, node->text);
			else
			{
				dup2(fd, STDIN_FILENO);
				if (close(fd) == -1)
					perror_ret(minishell);
				if (unlink(node->text) == -1)
					perror_ret(minishell);
			}
		}
		else if (node->token == REDIRECT_OUT)
		{
			fd = open(node->text, O_CREAT | O_WRONLY | O_TRUNC);
			if (fd == -1)
				perror_file(minishell, node->text);
			else
			{
				dup2(fd, STDOUT_FILENO);
				if (close(fd) == -1)
					perror_ret(minishell);
			}
		}
		else if (node->token == REDIRECT_OUT_APPEND)
		{
			fd = open(node->text, O_CREAT | O_WRONLY);
			if (fd == -1)
				perror_file(minishell, node->text);
			else
			{
				dup2(fd, STDOUT_FILENO);
				if (close(fd) == -1)
					perror_ret(minishell);
			}
		}
	}
	return (recursive_tree_read(minishell, node->child_left));
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
		free_msh(minishell);
		exit(status);
	}
	// pid = fork();
	// if (pid == -1)
	// 	return (perror_ret(minishell));
	// else if (pid == 0)
	// {
		status = recursive_tree_read(minishell, node->child_right);
		free_msh(minishell);
		exit(status);
	// }
	// status = 1;
	// waitpid(pid, &status, 0);
	// printf("status -> %d\n", status);
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

	// printf("ok %d, %s\n", minishell->ast_root->token, minishell->ast_root->text);
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