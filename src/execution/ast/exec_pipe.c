/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:12:08 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/11 16:13:04 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_left_pipe(t_minishell *minishell, t_ast_node *node)
{
	int	ret;

	if (close(minishell->pipe_fd[0]) == -1)
		perror("minishell");
	if (dup2(minishell->pipe_fd[1], STDOUT_FILENO) == -1)
		perror("minishell");
	if (close(minishell->pipe_fd[1]) == -1)
		perror("minishell");
	ret = recursive_tree_read(minishell, node->child_left);
	free_exit(minishell, ret);
	return (1);
}

int	exec_right_pipe(t_minishell *minishell, t_ast_node *node)
{
	int	ret;
	int	pid;

	ret = 1;
	pid = fork();
	if (pid == -1)
		return (perror_ret(minishell));
	if (pid == 0)
	{
		dup2(minishell->pipe_fd[0], STDIN_FILENO);
		close(minishell->pipe_fd[0]);
		ret = recursive_tree_read(minishell, node->child_right);
		free_exit(minishell, ret);
	}
	waitpid(pid, &ret, 0);
	ret = WEXITSTATUS(ret);
	return (ret);
}

int	exec_pipe(t_minishell *minishell, t_ast_node *node)
{
	int	ret;

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
			perror("minishell");
		ret = exec_right_pipe(minishell, node);
	}
	if (close(minishell->pipe_fd[0]) == -1)
		perror("minishell");
	waitpid(minishell->pid, NULL, 0);
	return (ret);
}
