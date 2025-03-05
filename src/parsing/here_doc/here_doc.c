/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:00:39 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/05 10:21:00 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gen_hd_name() {
	static int	counter = 0;

	return (params_to_string("/tmp/.minishell_heredoc_%d_%d", getpid(), counter++));
}

void	free_hd(t_cmd_part	*cmd_p, char *filename)
{
	free(cmd_p->text);
	cmd_p->text = NULL;
	free(filename);
}

void	create_here_doc(t_cmd_part	*cmd_p, char *filename)
{
	int		fd;
	int		eof_len;
	char	*ln;

	if (cmd_p->text == NULL || filename == NULL)
		return (free_hd(cmd_p, filename));
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (free_hd(cmd_p, filename));
	eof_len = ft_strlen(cmd_p->text);
	ln = readline("> ");
	while (ft_strncmp(ln, cmd_p->text, eof_len) != 0 && g_signal != SIGINT)
	{
		ft_putstr_fd(ln, fd);
		ft_putstr_fd("\n", fd);
		free(ln);
		ln = readline("> ");
	}
	free(ln);
	close(fd); // TODO ptet secur par la
	free(cmd_p->text);
	cmd_p->text = filename;
}

void	all_here_doc(t_minishell *minishell)
{
	t_cmd_part	*cmd_p;
	
	cmd_p = minishell->cmd_tokens;
	while (cmd_p)
	{
		if (tget_a(cmd_p) == HERE_DOC && tget_n(cmd_p) == FILE_R)
			create_here_doc(cmd_p->next, gen_hd_name());
		cmd_p = cmd_p->next;
	}
}
