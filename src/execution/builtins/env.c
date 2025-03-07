/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:45:00 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/07 12:15:34 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_bc(t_minishell *minishell, t_cmd_exec *cmd)
{
	print_env(minishell->env);
	free_cmd(cmd);
	return (0);
}
