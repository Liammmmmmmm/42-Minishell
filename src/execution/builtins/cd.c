/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:03:18 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/06 12:49:23 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// voir man chdir
#include "minishell.h"

int	cd_bc(t_minishell *minishell, t_cmd_exec *cmd)
{
	// char *home;
	// int argc;
	// argc = char_tab_len(cmd->cmd_n_args);
	// if (argc >= 3)
	// //TODO jsp trop comment tu veux gerer ca
	// else if (argc == 2 && argc[1][0] == '')
	// do fuck chdir
	// else if (argc == 2 && argc[1][0] != '')
	// do chdir
	// else if (argc == 1)
	(void)minishell;
	printf("oeoe tkt j'ai cd\n");
	free_cmd(cmd);
	return (0);
}
