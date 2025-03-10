/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:46:40 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/10 17:40:08 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gen_hd_name(void)
{
	static int	counter = 0;

	return (params_to_string("/tmp/.minishell_heredoc_%d_%d",
			getpid(), counter++));
}

void	free_hd(t_cmd_part	*cmd_p, char *filename, int fd)
{
	free(cmd_p->text);
	cmd_p->text = NULL;
	free(filename);
	close(STDIN_FILENO);
	if (fd != -1)
		close(fd);
}

int	unlink_here_doc_error(t_cmd_part *cmd_p)
{
	while (cmd_p)
	{
		if (tget_a(cmd_p) == FILE_R && tget_p(cmd_p) == HERE_DOC && cmd_p->text)
		{
			if (ft_strncmp(cmd_p->text, "/tmp/.minishell_heredoc_", 24) == 0)
			{
				unlink(cmd_p->text);
				free(cmd_p->text);
				cmd_p->text = NULL;
			}
		}
		cmd_p = cmd_p->previous;
	}
	return (-1);
}

void	unlink_here_doc(t_minishell *minishell)
{
	t_cmd_part	*cmd_p;

	cmd_p = minishell->cmd_tokens;
	while (cmd_p)
	{
		if (tget_a(cmd_p) == FILE_R && tget_p(cmd_p) == HERE_DOC)
		{
			if (ft_strncmp(cmd_p->text, "/tmp/.minishell_heredoc_", 24) == 0)
			{
				unlink(cmd_p->text);
				free(cmd_p->text);
				cmd_p->text = NULL;
			}
		}
		cmd_p = cmd_p->next;
	}
}

void	rm_quotes(char *delimiter)
{
	int	is_dq;
	int	is_sq;
	int	i;
	int	n;

	if (!delimiter)
		return ;
	is_dq = 0;
	is_sq = 0;
	i = 0;
	n = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == '"' && !is_sq)
			is_dq = !is_dq;
		else if (delimiter[i] == '\'' && !is_dq)
			is_sq = !is_sq;
		else
			delimiter[n++] = delimiter[i];
		i++;
	}
	delimiter[n] = '\0';
}
