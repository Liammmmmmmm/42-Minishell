/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:45:37 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/06 12:49:40 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_bc(t_minishell *minishell, t_cmd_exec *cmd)
{(void)minishell;
	printf("oeoe tkt j'ai export\n");
	free_cmd(cmd);
	return (0);
}
