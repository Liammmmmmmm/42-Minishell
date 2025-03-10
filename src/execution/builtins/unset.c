/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:47:48 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/10 11:19:46 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_bc(t_minishell *minishell, t_cmd_exec *cmd)
{
	int		argc;
	int		i;

	i = 1;
	argc = char_tab_len(cmd->cmd_n_args);
	while (i <= argc)
	{
		del_env_var(&(minishell->env), cmd->cmd_n_args[i]);
		i++;
	}
	free_cmd(cmd);
	return (0);
}
