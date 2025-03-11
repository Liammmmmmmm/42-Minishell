/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:39:43 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/11 10:19:25 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_success(t_minishell *minishell, t_ast_node *node, int fd)
{
	if (node->token == REDIRECT_IN || node->token == HERE_DOC)
	{
		minishell->have_red_in = 1;
		if (dup2(fd, STDIN_FILENO) == -1)
			perror("minishell");
	}
	else
	{
		minishell->have_red_out = 1;
		if (dup2(fd, STDOUT_FILENO) == -1)
			perror("minishell");
	}
	if (close(fd) == -1)
		perror("minishell");
	if (node->token == HERE_DOC)
	{
		if (unlink(node->text) == -1)
			perror("minishell");
		else
			node->text[0] = '\0';
	}
}

static int	before_recursive(t_minishell *minishell, t_ast_node *node, int nsuc)
{
	int	fd;

	fd = -1;
	if (node->token == REDIRECT_IN && nsuc)
		fd = open(node->text, O_RDONLY);
	else if (node->token == HERE_DOC && nsuc)
		fd = open(node->text, O_RDONLY);
	else if (node->token == REDIRECT_OUT && nsuc)
		fd = open(node->text, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (node->token == REDIRECT_OUT_APPEND && nsuc)
		fd = open(node->text, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror_file(minishell, node->text);
		return (0);
	}
	else
	{
		open_success(minishell, node, fd);
		return (1);
	}
}

static void	after_recursive(t_minishell *minishell, t_ast_node *node, int temp)
{
	if (node->token == REDIRECT_IN || node->token == HERE_DOC)
	{
		close(STDIN_FILENO);
		dup2(temp, STDIN_FILENO);
	}
	else
	{
		close(STDOUT_FILENO);
		dup2(temp, STDOUT_FILENO);
	}
	del_fd_garbage(&minishell->fd_garbage, temp);
}

int	exec_redirect(t_minishell *minishell, t_ast_node *node)
{
	int	temp;
	int	res;
	int	node_success;
	int	open_success;

	open_success = 0;
	if (node->text)
	{
		if (node->token == REDIRECT_IN || node->token == HERE_DOC)
			temp = dup(STDIN_FILENO);
		else
			temp = dup(STDOUT_FILENO);
		node_success = new_fd_garbage(&minishell->fd_garbage, temp);
		open_success = before_recursive(minishell, node, node_success);
	}
	if (open_success)
		res = recursive_tree_read(minishell, node->child_left);
	else
		res = 1;
	if (node->text && node_success)
		after_recursive(minishell, node, temp);
	return (res);
}
