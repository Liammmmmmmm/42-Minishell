/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:00:39 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/06 11:44:12 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gen_hd_name()
{
	static int	counter = 0;

	return (params_to_string("/tmp/.minishell_heredoc_%d_%d", getpid(), counter++));
}

void	free_hd(t_cmd_part	*cmd_p, char *filename)
{
	free(cmd_p->text);
	cmd_p->text = NULL;
	free(filename);
}

void	create_here_doc(t_cmd_part	*cmd_p, char *filename, t_minishell *minishell)
{
	int		fd;
	int		eof_len;
	char	*ln;

	if (cmd_p->text == NULL || filename == NULL)
	{
		free_hd(cmd_p, filename);
		free_exit(minishell, 1);
	}
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		free_hd(cmd_p, filename);
		free_exit(minishell, 1);
	}
	eof_len = ft_strlen(cmd_p->text);
	ln = readline("> ");
	while (g_signal != SIGINT && ft_strncmp(ln, cmd_p->text, eof_len) != 0)
	{
		ft_putstr_fd(ln, fd);
		ft_putstr_fd("\n", fd);
		free(ln);
		ln = readline("> ");
	}
	free_msh(minishell);
	free(ln);
	close(fd); // TODO ptet secur par la
	if (g_signal == SIGINT)
		exit(1);
	exit(0);
}

int	all_here_doc(t_minishell *minishell)
{
	t_cmd_part	*cmd_p;
	int			temp_fd;
	pid_t		pid;
	char		*hd_name;
	int			status;

	cmd_p = minishell->cmd_tokens;
	while (cmd_p)
	{
		if (tget_a(cmd_p) == HERE_DOC && tget_n(cmd_p) == FILE_R)
		{
			temp_fd = dup(STDIN_FILENO);
			// secure
			hd_name = gen_hd_name();
			// secure
			signal(SIGINT, signal_handler_here_doc);
			pid = fork();
			if (pid == -1)
				perror("minishell");
			else if (pid == 0)
				create_here_doc(cmd_p->next, hd_name, minishell);
			status = 0;
			waitpid(pid, &status, 0);
			dup2(temp_fd, STDIN_FILENO);
			// secure
			free(cmd_p->next->text);
			cmd_p->next->text = hd_name;
			if (WEXITSTATUS(status) == 1)
				return (-1);
		}
		cmd_p = cmd_p->next;
	}
	return (0);
}
