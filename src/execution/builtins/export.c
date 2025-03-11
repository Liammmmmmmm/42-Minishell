/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:45:37 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/11 12:08:47 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exprt_env(t_minishell *minishell, t_cmd_exec *cmd, char *var_name, int i)
{
	char	*temp;

	temp = malloc((i + 1) * sizeof(char));
	if (temp == NULL)
	{
		perror("minishell");
		free_cmd(cmd);
		return (1);
	}
	temp[0] = '\0';
	ft_strlcat(temp, var_name, i + 1);
	temp[i] = '\0';
	update_var_env(&(minishell->env), temp, &(var_name[i + 1]), 0);
	free(temp);
	return (0);
}

int	is_valid_var_name(char *var_name)
{
	int	i;

	if (var_name[0] != '_' && !ft_isalpha(var_name[0]))
		return (0);
	i = 1;
	while (var_name[i] && var_name[i] != '=')
	{
		if (!is_valid_var_char(var_name[i]))
			return (0);
		i++;
	}
	return (1);
}

int	manage_arg_exprt(t_minishell *minishell, t_cmd_exec *cmd, int argc)
{
	char	*var_name;
	size_t	i;
	int		j;
	int		status;

	j = 1;
	status = 0;
	while (j < argc && status == 0)
	{
		i = 0;
		var_name = cmd->cmd_n_args[j++];
		if (!is_valid_var_name(var_name))
		{
			other_error("export: not a valid identifier");
			continue ;
		}
		while (var_name[i] && var_name[i] != '=')
			i++;
		if (var_name[i] == '=')
			status = exprt_env(minishell, cmd, var_name, i);
		else
			update_var_env(&(minishell->env), var_name, NULL, 1);
	}
	return (status);
}

int	export_bc(t_minishell *minishell, t_cmd_exec *cmd)
{
	int		argc;
	int		status;

	status = 0;
	argc = char_tab_len(cmd->cmd_n_args);
	if (argc == 1)
		print_env_export(minishell->env);
	else
		status = manage_arg_exprt(minishell, cmd, argc);
	free_cmd(cmd);
	return (status);
}
