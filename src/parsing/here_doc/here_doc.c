/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:00:39 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/07 11:32:50 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gen_hd_name()
{
	static int	counter = 0;

	return (params_to_string("/tmp/.minishell_heredoc_%d_%d", getpid(), counter++));
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

void	create_here_doc(t_cmd_part	*cmd_p, char *filename, t_minishell *minishell)
{
	int		fd;
	int		eof_len;
	char	*ln;

	if (cmd_p->text == NULL || filename == NULL)
	{
		free_hd(cmd_p, filename, -1);
		free_exit(minishell, 1);
	}
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		free_hd(cmd_p, filename, -1);
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
	free(ln);
	free_hd(cmd_p, filename, fd);
	if (g_signal == SIGINT)
		free_exit(minishell, 1);
	free_exit(minishell, 0);
}

int	unlink_here_doc_error(t_cmd_part *cmd_p)
{
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
		cmd_p = cmd_p->previous;
	}
	return (-1);
}

void	unlink_here_doc(t_minishell *minishell)
{
	t_cmd_part *cmd_p;

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
			if (temp_fd == -1)
			{
				perror("minishell");
				return (unlink_here_doc_error(cmd_p->next));
			}
			hd_name = gen_hd_name();
			if (!hd_name)
			{
				close(temp_fd);
				return (unlink_here_doc_error(cmd_p->next));
			}
			signal(SIGINT, signal_handler_here_doc);
			pid = fork();
			if (pid == -1)
			{
				close(temp_fd);
				free(hd_name);
				perror("minishell");
				return (unlink_here_doc_error(cmd_p->next));
			}
			else if (pid == 0)
			{
				signal(SIGINT, signal_handler_child);
				close(temp_fd);
				create_here_doc(cmd_p->next, hd_name, minishell);
			}
			status = 0;
			waitpid(pid, &status, 0);
			if (dup2(temp_fd, STDIN_FILENO) == -1)
			{
				perror("minishell");
				close(temp_fd);
				free(hd_name);
				free_exit(minishell, 1);
			}
			close(temp_fd);
			free(cmd_p->next->text);
			cmd_p->next->text = hd_name;
			if (WEXITSTATUS(status) == 1)
				return (unlink_here_doc_error(cmd_p->next));
		}
		cmd_p = cmd_p->next;
	}
	return (0);
}
