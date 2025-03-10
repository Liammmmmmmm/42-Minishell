/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:44:09 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/10 16:46:15 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_null_cmd(t_minishell *minishell)
{
	char	*line;

	if (minishell->have_red_in && minishell->have_red_out)
	{
		line = get_next_line(0);
		while (line)
		{
			write(1, line, ft_strlen(line));
			free(line);
			line = get_next_line(0);
		}
	}
	return (0);
}

int	is_builtins(t_cmd_exec *cmd)
{
	if (strcmp(cmd->cmd_n_args[0], "cd") == 0
		|| strcmp(cmd->cmd_n_args[0], "env") == 0
		|| strcmp(cmd->cmd_n_args[0], "pwd") == 0
		|| strcmp(cmd->cmd_n_args[0], "echo") == 0
		|| strcmp(cmd->cmd_n_args[0], "exit") == 0
		|| strcmp(cmd->cmd_n_args[0], "unset") == 0
		|| strcmp(cmd->cmd_n_args[0], "export") == 0)
		return (1);
	return (0);
}

int	exec_builtins(t_minishell *minishell, t_cmd_exec *cmd)
{
	if (strcmp(cmd->cmd_n_args[0], "echo") == 0)
		return (echo_bc(minishell, cmd));
	else if (strcmp(cmd->cmd_n_args[0], "cd") == 0)
		return (cd_bc(minishell, cmd));
	else if (strcmp(cmd->cmd_n_args[0], "pwd") == 0)
		return (pwd_bc(minishell, cmd));
	else if (strcmp(cmd->cmd_n_args[0], "export") == 0)
		return (export_bc(minishell, cmd));
	else if (strcmp(cmd->cmd_n_args[0], "unset") == 0)
		return (unset_bc(minishell, cmd));
	else if (strcmp(cmd->cmd_n_args[0], "env") == 0)
		return (env_bc(minishell, cmd));
	else if (strcmp(cmd->cmd_n_args[0], "exit") == 0)
		return (exit_bc(minishell, cmd));
	else
		return (1);
}

int	is_cmd_export(char *cmd_text)
{
	int	i;

	if (cmd_text)
	{
		i = 0;
		while (ft_isspace(cmd_text[i]) || cmd_text[i] == '"'
			|| cmd_text[i] == '\'')
			i++;
		if (ft_strncmp(&cmd_text[i], "export", 7) == 0)
			return (1);
	}
	return (0);
}

void	free_cmd(t_cmd_exec *cmd)
{
	if (cmd->full_cmd && cmd->full_cmd != cmd->og_text)
		free(cmd->full_cmd);
	if (cmd->cmd_n_args)
		ft_free_tab(cmd->cmd_n_args, char_tab_len(cmd->cmd_n_args));
	if (cmd->paths)
		ft_free_tab_null_term(cmd->paths);
	if (cmd->right_path)
		free(cmd->right_path);
}
