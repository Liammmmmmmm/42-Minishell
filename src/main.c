/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:27:01 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/03 11:47:10 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_msh(t_minishell *minishell)
{
	clean_tokenized_cmd(minishell);
	free_tree(minishell->ast_root);
	rl_clear_history();
}

int	main(int argc, char **argv, char **env)
{
	int	stop;
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	minishell.ast_root = NULL;
	minishell.cmd_tokens = NULL;
	minishell.env = env;
	minishell.last_res = 0;
	stop = 0;
	init_sighandler();
	while (stop == 0)
		display_prompt(&stop, &minishell);
	rl_clear_history();
}