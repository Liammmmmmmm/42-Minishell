/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:40:33 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/10 12:13:17 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	manage_error_access(t_cmd_exec *cmd)
{
	if (cmd->cmd_perm == -2)
	{
		permission_denied(cmd->right_path, cmd->cmd_n_args[0]);
		cmd->status = 126;
	}
	else if (cmd->cmd_perm == -3)
	{
		other_error("Malloc failed");
		cmd->status = 1;
	}
	else
	{
		cmd_not_found(cmd->cmd_n_args[0]);
		cmd->status = 127;
	}
	free_cmd(cmd);
	return (cmd->status);
}

static int	exec_cmd_and_fork(t_minishell *minishell, t_cmd_exec *cmd)
{
	int	ret;

	minishell->pid = fork();
	if (minishell->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		free_msh(minishell);
		if (execve(cmd->right_path, cmd->cmd_n_args,
				construct_env(minishell->env)) == -1)
		{
			free(cmd->right_path);
			free_cmd(cmd);
			rl_clear_history();
			exit(1);
		}
	}
	waitpid(minishell->pid, &ret, 0);
	free_cmd(cmd);
	if (ret == 131)
		ft_dprintf(2, "Quit (core dumped)\n");
	return (ret);
}

int	exec_cmd(t_ast_node *command, t_minishell *minishell)
{
	t_cmd_exec	cmd;
	int			ret;

	if (command->text == NULL)
		return (manage_null_cmd(minishell));
	ret = init_cmd_exec(&cmd, command->text, minishell);
	if (ret != 0)
		return (ret);
	if (is_builtins(&cmd))
		return (exec_builtins(minishell, &cmd));
	if (cmd.cmd_perm == 1)
		return (exec_cmd_and_fork(minishell, &cmd));
	else
		return (manage_error_access(&cmd));
	free_cmd(&cmd);
	return (1);
}
