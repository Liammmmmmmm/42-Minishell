/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:45:25 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/07 12:01:57 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_bc(t_minishell *minishell, t_cmd_exec *cmd)
{
	printf("See you later !\n");
	free_cmd(cmd);
	free_exit(minishell, 0); // TODO on peut passer un arg au exit pour exit avec un certain code
	return (1);
}

int	exit_eof(t_minishell *minishell)
{
	printf("See you later !\n");
	free_exit(minishell, 130);
	return (1);
}
