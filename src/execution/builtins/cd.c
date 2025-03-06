/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:03:18 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/06 15:58:19 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// voir man chdir
#include "minishell.h"

int	cd_bc(t_minishell *minishell, t_cmd_exec *cmd)
{
	char *home;
	char *path;
	int argc;
	
	argc = char_tab_len(cmd->cmd_n_args);
	if (argc >= 3)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	else if (argc == 2 && cmd->cmd_n_args[1][0] != '~')
	{
		if (chdir(cmd->cmd_n_args[1]) == -1)
		{
			free_cmd(cmd);
			perror("minishell");
			return (1);
		}
	}
	else if (argc == 2 && cmd->cmd_n_args[1][0] == '~')
	{
		home = get_env_variable(minishell->env, "$HOME");
		if (home == NULL)
			home = "/";
		path = malloc((ft_sstrlen(home) + ft_sstrlen(cmd->cmd_n_args[1]) + 2) * sizeof(char));
		if (path == NULL)
		{
			free_cmd(cmd);
			perror("minishell");
			return (1);
		}
		ft_memcpy(path, home, ft_sstrlen(home));
		path[ft_sstrlen(home)] = '/';
		ft_memcpy(path + ft_sstrlen(home) + 1, cmd->cmd_n_args[1], ft_sstrlen(cmd->cmd_n_args[1]));
		if (chdir(path) == -1)
		{
			free_cmd(cmd);
			perror("minishell");
			return (1);
		}
	}
	else if (argc == 1)
	{
		home = get_env_variable(minishell->env, "$HOME");
		if (home == NULL)
			home = "/";
		if (chdir(home) == -1)
		{
			free_cmd(cmd);
			perror("minishell");
			return (1);
		}
	}
	free_cmd(cmd);
	return (0);
}
