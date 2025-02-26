/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:27:01 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/25 14:10:13 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	int	stop;
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	// printf("%s", replace_variables("$test '$test' \"$test\""));
	// char **tabs = split_args(replace_variables("$test '$test' \"$test\""));
	minishell.ast_root = NULL;
	minishell.cmd_tokens = NULL;
	minishell.env = env;
	stop = 0;
	init_sighandler();
	while (stop == 0)
		display_prompt(&stop, &minishell);
	rl_clear_history();
}