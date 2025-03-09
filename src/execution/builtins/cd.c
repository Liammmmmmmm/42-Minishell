/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:03:18 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/09 11:39:13 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// voir man chdir
#include "minishell.h"

int	free_cmd_path_errno(t_cmd_exec *cmd, char *path, int error_flag)
{
	if (path)
		free(path);
	path = NULL;
	free_cmd(cmd);
	if (error_flag)
		perror("minishell");
	return (1);
}
// TODO fix : minishell: No such file or directory peu importe ou on va

void concat_home(t_minishell *minishell, t_cmd_exec *cmd, char *arg)
{
	char	*temp;
	char	*path;
	int		len_temp;
	int		len_arg;
	
	temp = get_env_variable(minishell->env, "HOME");
	if (temp == NULL)
		temp = "/";
	len_temp = ft_sstrlen(temp);
	len_arg = ft_sstrlen(arg);
	path = malloc((len_temp + len_arg + 2) * sizeof(char));
	if (path == NULL)
		free_cmd_path_errno(cmd, path, 1);
	ft_memcpy(path, temp, len_temp);
	path[len_temp] = '/';
	ft_memcpy(path + len_temp + 1, arg, len_arg);
	if (chdir(path) == -1)
		free_cmd_path_errno(cmd, path, 1);
	free(path);
}

int	cd_bc(t_minishell *minishell, t_cmd_exec *cmd)
{
	char *temp;
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
			return (free_cmd_path_errno(cmd, NULL, 1));
	}
	else if (argc == 2 && cmd->cmd_n_args[1][0] == '~')
		concat_home(minishell, cmd, cmd->cmd_n_args[1]);
	else if (argc == 1)
	{
		temp = get_env_variable(minishell->env, "HOME");
		if (temp == NULL)
			temp = "/";
		if (chdir(temp) == -1)
			return (free_cmd_path_errno(cmd, NULL, 1));
	}
	temp = getcwd(NULL, 0);
	update_var_env(&(minishell->env), "PWD", temp);
	free_cmd_path_errno(cmd, NULL, 0);
	return (0);
}
