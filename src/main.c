/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:27:01 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/25 11:58:35 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	int	stop;
	t_minishell	minishell;

	// printf("%s", replace_variables("$test '$test' \"$test\""));
	// char **tabs = split_args(replace_variables("$test '$test' \"$test\""));
	minishell.ast_root = NULL;
	minishell.cmd_tokens = NULL;
	stop = 0;
	init_sighandler();
	while (stop == 0)
		display_prompt(&stop, &minishell);
	rl_clear_history();
}