/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:40:33 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/27 16:16:00 by lilefebv         ###   ########lyon.fr   */
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
{ // TODO Fix segfault si cmd = ""
	cmd->cmd_perm = 0;
	cmd->cmd_n_args = NULL;
	cmd->full_cmd = NULL;
	cmd->path = NULL;
	cmd->paths = NULL;
	cmd->right_path = NULL;
	cmd->og_text = cmd_text;
	// verif si la command est pas export pour mettre l'arg 1 entre double quotes
	cmd->full_cmd = replace_variables(cmd_text, minishell->last_res);
	if (!cmd->full_cmd)
		return (free_cmd(cmd), -1);
	cmd->cmd_n_args = split_args(cmd->full_cmd);
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

int	exec_cmd(t_ast_node *command, t_minishell *minishell)
{
	t_cmd_exec	cmd;

	if (init_cmd_exec(&cmd, command->text, minishell) == -1)
		return (1);
	// TODO si c'est une des commandes "brutes" l'executer
	if (cmd.cmd_perm == 1)
	{
		command->pid = fork();
		if (command->pid == -1)
			perror("minishell");
		else if (command->pid == 0)
		{
			// TODO la dcp faut free tout le programme en gros
			if (execve(cmd.right_path, cmd.cmd_n_args, minishell->env) == -1) // TODO gerer le retour pour bien avoir le retours de la commande ou autre si autre erreure genre malloc -> faut le faire avec waitpid, mais dcp faut le faire que sur les trucs avant les operteurs || ou && et sur le dernier node
			{
				// TODO y'a une erreur donc faut bien tout free
				free(cmd.right_path);
				free_cmd(&cmd);
				exit(1);
			}
		}
		else
			free(cmd.right_path);
	}
	else
	{
		if (cmd.cmd_perm == -2)
		{
			permission_denied(cmd.right_path, cmd.cmd_n_args[0]);
			minishell->last_res = 126;
		}
		else if (cmd.cmd_perm == -3)
		{
			other_error("Malloc failed");
			minishell->last_res = 1;
		}
		else
		{
			cmd_not_found(cmd.cmd_n_args[0]);
			minishell->last_res = 127;
		}
	}
	free_cmd(&cmd);
	return (0);
}
