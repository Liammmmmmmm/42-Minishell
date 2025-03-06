/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:40:33 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/06 12:53:32 by lilefebv         ###   ########lyon.fr   */
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

void	free_cmd(t_cmd_exec *cmd)
{
	// if (cmd->og_text) // ca fait des double free ca !!!!
	// 	free(cmd->og_text);
	if (cmd->full_cmd)
		free(cmd->full_cmd);
	if (cmd->cmd_n_args)
		ft_free_tab(cmd->cmd_n_args, char_tab_len(cmd->cmd_n_args));
	if (cmd->paths)
		ft_free_tab_null_term(cmd->paths);
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
		if (access(pathcmd, F_OK) != 0)
		{
			if (errno == ENOENT && cmd->cmd_perm != -2)
				cmd->cmd_perm = -1;
			free(pathcmd);
			continue ;
		}
		if (access(pathcmd, X_OK) != 0)
		{
			if (errno == EACCES)
			{
				cmd->cmd_perm = -2;
				cmd->right_path = cmd->paths[i];
			}
			free(pathcmd);
			continue ;
		}
		cmd->right_path = pathcmd;
		cmd->cmd_perm = 1;
		return ;
	}
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
	// TODO verif si la command est pas export pour mettre l'arg 1 entre double quotes
	cmd->full_cmd = replace_variables(cmd_text, minishell->last_res);
	cmd->full_cmd = replace_wildcards(cmd->full_cmd);
	cmd->cmd_n_args = split_args(cmd->full_cmd);
	if (!cmd->cmd_n_args[0])
	{
		cmd_not_found("");
		free_cmd(cmd);
		free_exit(minishell, 127);
	}
	if (!cmd->cmd_n_args)
		return (free_cmd(cmd), -1);
	if (ft_strchr(cmd->cmd_n_args[0], '/'))
	{
		cmd->right_path = ft_strdup(cmd->cmd_n_args[0]);
		cmd->cmd_perm = -3;
		if (cmd->right_path)
			cmd->cmd_perm = 1;
	}
	else
	{
		cmd->path = getenv("PATH");
		cmd->paths = ft_split(cmd->path, ":");
		if (!cmd->paths)
			return (free_cmd(cmd), -1);
		find_right_path(cmd);
	}
	return (0);
}

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
	free_exit(minishell, 0);
	return (1);
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

int	exec_cmd(t_ast_node *command, t_minishell *minishell)
{
	t_cmd_exec	cmd;
	int			ret;

	if (command->text == NULL)
		return (manage_null_cmd(minishell));
	if (init_cmd_exec(&cmd, command->text, minishell) == -1)
		return (1);
	if (is_builtins(&cmd))
		return (exec_builtins(minishell, &cmd));
	if (cmd.cmd_perm == 1)
	{
		minishell->pid = fork();
		if (minishell->pid == 0)
		{
			free_msh(minishell);
			if (execve(cmd.right_path, cmd.cmd_n_args, minishell->env) == -1)
			{
				free(cmd.right_path);
				free_cmd(&cmd);
				rl_clear_history();
				exit(1);
			}
		}
		waitpid(minishell->pid, &ret, 0);
		free_cmd(&cmd);
		return (ret);
	}
	else
	{
		if (cmd.cmd_perm == -2)
		{
			permission_denied(cmd.right_path, cmd.cmd_n_args[0]);
			cmd.status = 126;
		}
		else if (cmd.cmd_perm == -3)
		{
			other_error("Malloc failed");
			cmd.status = 1;
		}
		else
		{
			cmd_not_found(cmd.cmd_n_args[0]);
			cmd.status = 127;
		}
		free_cmd(&cmd);
		return (cmd.status);
	}
	free_cmd(&cmd);
	return (1);
}
