/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:47:48 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/06 12:49:44 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_bc(t_minishell *minishell, t_cmd_exec *cmd)
{(void)minishell;
	printf("oeoe tkt j'ai unset\n");
	free_cmd(cmd);
	return (0);
}
