/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:47:32 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/05 15:28:32 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// getcwd man
#include "minishell.h"

void	pwd_bc(t_minishell *minishell, t_cmd_exec *cmd)
{
	(void)minishell;
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	if (cwd[0] == '\0')
	{
		perror("minishell");
		free_cmd(cmd);
		//return (1);
	}
	printf("%s", cwd);
	free_cmd(cmd);
	//return (0);
}
