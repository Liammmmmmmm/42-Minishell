/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:45:00 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/04 16:49:35 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_bc(t_minishell *minishell, t_cmd_exec *cmd)
{
	printf("oeoe tkt j'ai fais env\n");
	free_cmd(cmd);
	free_exit(minishell, 0);
}
