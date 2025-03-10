/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:42:53 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/10 13:52:00 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exit(t_minishell *minishell, int ret)
{
	free_msh(minishell);
	free_env(minishell->env);
	exit(ret);
}

int	free_ret(t_minishell *minishell, int ret)
{
	free_msh(minishell);
	return (ret);
}

int	perror_ret(t_minishell *minishell)
{
	perror("minishell");
	minishell->last_res = 1;
	return (1);
}

void	perror_exit(t_minishell *minishell)
{
	perror("minishell");
	free_exit(minishell, 1);
}
