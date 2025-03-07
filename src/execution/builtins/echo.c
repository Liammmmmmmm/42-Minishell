/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:08:16 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/07 12:16:17 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_bc(t_minishell *minishell, t_cmd_exec *cmd)
{
	int	print_nl;
	int	i;

	(void)minishell;
	print_nl = 1;
	if (char_tab_len(cmd->cmd_n_args) >= 2)
	{
		if (ft_strcmp(cmd->cmd_n_args[1], "-n") == 0)
			print_nl = 0;
	}
	i = 1;
	while (cmd->cmd_n_args[i])
	{
		printf("%s", cmd->cmd_n_args[i]);
		i++;
		if (cmd->cmd_n_args[i])
			printf(" ");
	}
	if (print_nl)
		printf("\n");
	free_cmd(cmd);
	return (0);
}
