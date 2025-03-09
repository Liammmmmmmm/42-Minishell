/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:03:18 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/09 17:35:29 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// voir man chdir
#include "minishell.h"

int	free_cmd_path_errno(t_cmd_exec *cmd, int error_flag)
{
	free_cmd(cmd);
	if (error_flag == 1)
		perror("minishell");
	else if (error_flag == 2)
		ft_dprintf(2,"%s\n", "minishell: cd: HOME not set");
	return (error_flag != 0);
}

int	cd_bc(t_minishell *minishell, t_cmd_exec *cmd)
{
	char *old_pwd;
	char *temp;
	int argc;
	
	argc = char_tab_len(cmd->cmd_n_args);
	if (argc >= 3)
	{
		ft_dprintf(2,"%s\n", "minishell: too many arguments");
		return (1);
	}
	else if (argc == 2 && chdir(cmd->cmd_n_args[1]) == -1)
		return (free_cmd_path_errno(cmd, 1));
	else if (argc == 1)
	{
		temp = get_env_variable(minishell->env, "HOME");
		if (temp == NULL)
			return (free_cmd_path_errno(cmd, 2));
		else if (chdir(temp) == -1)
			return (free_cmd_path_errno(cmd, 1));
	}
	temp = getcwd(NULL, PATH_MAX);
	old_pwd = get_env_variable(minishell->env, "PWD");
	update_var_env(&(minishell->env), "OLDPWD", old_pwd, 0);
	update_var_env(&(minishell->env), "PWD", temp, 0);
	free(temp);
	return (free_cmd_path_errno(cmd, 0));
}
