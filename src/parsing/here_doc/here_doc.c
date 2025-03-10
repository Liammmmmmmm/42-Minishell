/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:00:39 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/10 17:40:53 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_file(t_cmd_part *cmd_p, char *filename, t_minishell *minishell)
{
	int	fd;

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
	return (fd);
}

void	create_here_doc(t_cmd_part *cmd_p, char *filename, t_minishell *msh)
{
	int		fd;
	int		eof_len;
	char	*ln;
	int		count_ln;

	fd = create_file(cmd_p, filename, msh);
	rm_quotes(cmd_p->text);
	eof_len = ft_strlen(cmd_p->text);
	count_ln = 1;
	ln = readline("> ");
	while (ln && g_signal != SIGINT && ft_strncmp(ln, cmd_p->text, eof_len + 1) != 0)
	{
		ft_putstr_fd(ln, fd);
		ft_putstr_fd("\n", fd);
		free(ln);
		count_ln++;
		ln = readline("> ");
	}
	if (!ln)
		ft_dprintf(2, CTRLD_HERE_DOC, count_ln, cmd_p->text);
	free(ln);
	free_hd(cmd_p, filename, fd);
	if (g_signal == SIGINT)
		free_exit(msh, 130);
	free_exit(msh, 0);
}

static int	init_fork(int *temp_fd, t_cmd_part *cmd_p, pid_t *pid, char *hd_n)
{
	*temp_fd = dup(STDIN_FILENO);
	if (*temp_fd == -1)
	{
		perror("minishell");
		return (unlink_here_doc_error(cmd_p->next));
	}
	signal(SIGINT, signal_handler_here_doc);
	*pid = fork();
	if (*pid == -1)
	{
		close(*temp_fd);
		free(hd_n);
		perror("minishell");
		return (unlink_here_doc_error(cmd_p->next));
	}
	return (0);
}

static int	all_here_doc_itt(t_cmd_part *cmd_p, t_minishell *minishell,
	char *hd_name)
{
	int		temp_fd;
	int		status;
	pid_t	pid;

	if (init_fork(&temp_fd, cmd_p, &pid, hd_name) == -1)
		return (-1);
	if (pid == 0)
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
	return (status);
}

int	all_here_doc(t_minishell *minishell)
{
	t_cmd_part	*cmd_p;
	int			status;
	char		*hd_name;

	cmd_p = minishell->cmd_tokens;
	while (cmd_p)
	{
		if (tget_a(cmd_p) == HERE_DOC && tget_n(cmd_p) == FILE_R)
		{
			hd_name = gen_hd_name();
			if (!hd_name)
				return (unlink_here_doc_error(cmd_p->next));
			status = all_here_doc_itt(cmd_p, minishell, hd_name);
			if (WEXITSTATUS(status) == 1)
				return (unlink_here_doc_error(cmd_p->next));
		}
		cmd_p = cmd_p->next;
	}
	return (0);
}
