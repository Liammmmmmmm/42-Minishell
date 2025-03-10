/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:47:32 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/10 14:20:01 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_bc(t_minishell *minishell, t_cmd_exec *cmd)
{
	char	*cwd;

	(void)minishell;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("minishell");
		free_cmd(cmd);
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	free_cmd(cmd);
	return (0);
}
