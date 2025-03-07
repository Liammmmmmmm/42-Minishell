/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:45:37 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/07 12:41:41 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_bc(t_minishell *minishell, t_cmd_exec *cmd)
{
	int		argc;
	size_t	i;
	char *var_name;
	char *temp;
	
	argc = char_tab_len(cmd->cmd_n_args);
	if (argc == 1)
		print_env_export(minishell->env);
	else
	{
		i = 0;
		var_name = cmd->cmd_n_args[1];
		while (var_name[i] && var_name[i] != '=')
			i++;
		if (var_name[i] == '=')
		{
			temp = maloc((ft_sstrlen(var_name) + 3) * sizeof(char));
			if (temp == NULL)
			{
				perror("minishell");
				free_cmd(cmd);
				return (1);
			}
			ft_strlcat(temp, var_name, i)
		}
		else
			add_end_env(var_name);
	}
	free_cmd(cmd);
	return (0);
}
