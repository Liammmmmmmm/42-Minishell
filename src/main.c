/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:27:01 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/24 15:18:49 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	int	stop;
	t_minishell	minishell;

	printf("%s", replace_variables("$test"));
	minishell.ast_root = NULL;
	minishell.cmd_tokens = NULL;
	stop = 0;
	while (stop == 0)
		display_prompt(&stop, &minishell);
	rl_clear_history();
}