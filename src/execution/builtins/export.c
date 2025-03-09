/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:45:37 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/09 17:05:46 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_bc(t_minishell *minishell, t_cmd_exec *cmd)
{
	int		argc;
	size_t	i;
	int		j;
	char *var_name;
	char *temp;
	
	argc = char_tab_len(cmd->cmd_n_args);
	if (argc == 1)
		print_env_export(minishell->env);
	else
	{
		j = 1;
		while (j < argc)
		{
			i = 0;
			var_name = cmd->cmd_n_args[j];
			while (var_name[i] && var_name[i] != '=')
				i++;
			if (var_name[i] == '=')
			{
				temp = malloc((ft_sstrlen(var_name) + 1) * sizeof(char));
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
			}
			else
				update_var_env(&(minishell->env), var_name, NULL, 1);
			j++;
		}
	}
	free_cmd(cmd);
	return (0);
}
