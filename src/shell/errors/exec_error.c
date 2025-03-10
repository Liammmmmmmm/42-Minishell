/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:45:30 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/10 13:52:00 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_not_found(char *cmd)
{
	ft_dprintf(2, "%s: command not found\n", cmd);
}

void	permission_denied(char *path, char *cmd)
{
	ft_dprintf(2, "minishell: %s/%s: Permission denied\n", path, cmd);
}

int	perror_file(t_minishell *minishell, char *filename)
{
	ft_dprintf(2, "minishell: %s: No such file or directory\n", filename);
	minishell->last_res = 1;
	return (1);
}
