/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:47:32 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/04 16:49:48 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// getcwd man
#include "minishell.h"

void	pwd_bc(t_minishell *minishell, t_cmd_exec *cmd)
{
	printf("oeoe tkt j'ai pwd\n");
	free_cmd(cmd);
	free_exit(minishell, 0);
}
