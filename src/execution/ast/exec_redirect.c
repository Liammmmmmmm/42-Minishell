/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:39:43 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/07 10:19:15 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_redirect(t_minishell *minishell, t_ast_node *node)
{
	int	fd;
	int	temp;
	int	res;

	if (node->text)
	{
		if (node->token == REDIRECT_IN || node->token == HERE_DOC)
			temp = dup(STDIN_FILENO);
		else
			temp = dup(STDOUT_FILENO);
		// secure
		fd = -1;
		if (node->token == REDIRECT_IN)
			fd = open(node->text, O_RDONLY);
		else if (node->token == HERE_DOC)
			fd = open(node->text, O_RDONLY);
		else if (node->token == REDIRECT_OUT)
			fd = open(node->text, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (node->token == REDIRECT_OUT_APPEND)
			fd = open(node->text, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
			perror_file(minishell, node->text);
		else
		{
			if (node->token == REDIRECT_IN || node->token == HERE_DOC)
			{
				minishell->have_red_in = 1;
				if (dup2(fd, STDIN_FILENO) == -1)
					perror_exit(minishell);
			}	
			else
			{
				minishell->have_red_out = 1;
				if (dup2(fd, STDOUT_FILENO) == -1)
					perror_exit(minishell);
			}
			if (close(fd) == -1)
				perror_ret(minishell);
			if (node->token == HERE_DOC)
			{
				if (unlink(node->text) == -1)
					perror_ret(minishell);
				else
					node->text[0] = '\0';
			}
		}
	}
	res = recursive_tree_read(minishell, node->child_left);
	if (node->text)
	{
		if (node->token == REDIRECT_IN || node->token == HERE_DOC)
		{
			close(STDIN_FILENO); // secure
			dup2(temp, STDIN_FILENO);
		}
		else
		{
			close(STDOUT_FILENO); // secure
			dup2(temp, STDOUT_FILENO);
		}
		close(temp);
	}
	return (res);
}