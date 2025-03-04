/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:03:18 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/04 16:49:26 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// voir man chdir
#include "minishell.h"

void	cd_bc(t_minishell *minishell, t_cmd_exec *cmd)
{
	printf("oeoe tkt j'ai cd\n");
	free_cmd(cmd);
	free_exit(minishell, 0);
}
