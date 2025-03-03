/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:12:08 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/03 16:56:40 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//TODO: Secure fork and dup
int exec_left_pipe(t_minishell *minishell, t_ast_node *node)
{
	int ret;
	
	if (close(minishell->pipe_fd[0]) == -1)
		perror_ret(minishell);
	dup2(minishell->pipe_fd[1], STDOUT_FILENO);
	if (close(minishell->pipe_fd[1]) == -1)
		perror_ret(minishell);
	ret = recursive_tree_read(minishell, node->child_left);
	free_msh(minishell);
	exit(ret);
}

int exec_right_pipe(t_minishell *minishell, t_ast_node *node)
{
	int	ret;
	int pid;
	ret = 1;
	pid = fork();
	if (pid == -1)
		return (perror_ret(minishell));
	if (pid == 0)
	{	
		dup2(minishell->pipe_fd[0], STDIN_FILENO);
		close(minishell->pipe_fd[0]);
		ret = recursive_tree_read(minishell, node->child_right);
		free_msh(minishell);
		exit(ret);
	}
	waitpid(pid, &ret, 0);
	return (ret);
}

int	exec_pipe(t_minishell *minishell, t_ast_node *node)
{
	int ret;
	
	ret = 1;

	if (pipe(minishell->pipe_fd) == -1)
		return (perror_ret(minishell));
	minishell->pid = fork();
	if (minishell->pid == -1)
		return (perror_ret(minishell));
	else if (minishell->pid == 0)
		exec_left_pipe(minishell, node);
	else
	{
		if (close(minishell->pipe_fd[1]) == -1)
			perror_ret(minishell);
		ret = exec_right_pipe(minishell, node);
	}
	if (close(minishell->pipe_fd[0]) == -1)
		perror_ret(minishell);
	waitpid(minishell->pid, NULL, 0);
	return (ret);
}
