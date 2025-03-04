/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:47:48 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/04 16:49:55 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_bc(t_minishell *minishell, t_cmd_exec *cmd)
{
	printf("oeoe tkt j'ai unset\n");
	free_cmd(cmd);
	free_exit(minishell, 0);
}
