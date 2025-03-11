/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:47:38 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/11 16:07:04 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static int	cmd_have_access(t_cmd_exec *cmd, char *pathcmd, int i, int fr)
{
	if (access(pathcmd, F_OK) != 0)
	{
		if (errno == ENOENT && cmd->cmd_perm != -2)
			cmd->cmd_perm = -1;
		if (fr)
			free(pathcmd);
		return (0);
	}
	if (access(pathcmd, X_OK) != 0)
	{
		if (errno == EACCES)
		{
			cmd->cmd_perm = -2;
			if (fr)
				cmd->right_path = cmd->paths[i];
		}
		if (fr)
			free(pathcmd);
		return (0);
	}
	return (1);
}

void	find_right_path(t_cmd_exec *cmd)
{
	int		i;
	char	*pathcmd;

	i = -1;
	while (cmd->paths[++i])
	{
		pathcmd = ft_strjoin(cmd->paths[i], "/");
		if (!pathcmd)
			continue ;
		pathcmd = ft_strjoin_free_buff(pathcmd, cmd->cmd_n_args[0]);
		if (!pathcmd)
			continue ;
		if (cmd_have_access(cmd, pathcmd, i, 1) == 0)
			continue ;
		cmd->right_path = pathcmd;
		cmd->cmd_perm = 1;
		return ;
	}
}

static int	abs_or_relative(t_cmd_exec *cmd, t_minishell *minishell)
{
	if (ft_strchr(cmd->cmd_n_args[0], '/'))
	{
		cmd->right_path = ft_strdup(cmd->cmd_n_args[0]);
		cmd->cmd_perm = -3;
		if (cmd->right_path)
			cmd->cmd_perm = 1;
		cmd_have_access(cmd, cmd->right_path, 0, 0);
	}
	else if (!is_builtins(cmd))
	{
		cmd->path = get_env_variable(minishell->env, "PATH");
		if (!cmd->path)
		{
			free_cmd(cmd);
			ft_dprintf(2, "minishell: Can't find PATH\n");
			return (-1);
		}
		cmd->paths = ft_split(cmd->path, ":");
		if (!cmd->paths)
			return (free_cmd(cmd),
				-1);
		find_right_path(cmd);
	}
	return (0);
}

int	init_cmd_exec(t_cmd_exec *cmd, char *cmd_text, t_minishell *minishell)
{
	cmd->cmd_perm = 0;
	cmd->cmd_n_args = NULL;
	cmd->full_cmd = NULL;
	cmd->path = NULL;
	cmd->paths = NULL;
	cmd->right_path = NULL;
	cmd->og_text = cmd_text;
	cmd->full_cmd = replace_variables(minishell, cmd_text, minishell->last_res,
			is_cmd_export(cmd_text));
	cmd->full_cmd = replace_wildcards(cmd->full_cmd);
	cmd->cmd_n_args = split_args(cmd->full_cmd);
	if (!cmd->cmd_n_args)
		return (free_cmd(cmd),
			1);
	if (!cmd->cmd_n_args[0])
	{
		cmd_not_found("");
		free_cmd(cmd);
		return (127);
	}
	if (!cmd->cmd_n_args)
		return (free_cmd(cmd), -1);
	if (abs_or_relative(cmd, minishell) == -1)
		return (-1);
	return (0);
}
