/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:27:01 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/12 13:01:17 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_msh(t_minishell *minishell)
{
	clean_tokenized_cmd(minishell);
	free_tree(minishell);
	clear_fd_garbage(minishell->fd_garbage);
	rl_clear_history();
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;


	if (!isatty(STDOUT_FILENO) || !isatty(STDIN_FILENO))
	{
		other_error("not a tty");
		exit(EXIT_FAILURE);
	}
	(void)argc;
	(void)argv;
	minishell.ast_root = NULL;
	minishell.cmd_tokens = NULL;
	minishell.env = get_chain_env(env, 0);
	minishell.last_res = 0;
	minishell.have_red_in = 0;
	minishell.have_red_out = 0;
	minishell.fd_garbage = NULL;
	while (1)
		display_prompt(&minishell);
}
