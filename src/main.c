/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:27:01 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/13 12:25:02 by lilefebv         ###   ########lyon.fr   */
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

void	update_shell_level(t_minishell *minishell)
{
	int		shell_level;
	char	*shlvl;
	
	shlvl = get_env_variable(minishell->env, "SHLVL");
	if (!shlvl)
		return ;
	shell_level = ft_atoi(shlvl);
	shlvl = ft_itoa(shell_level + 1);
	if (shlvl)
		update_var_env(&minishell->env, "SHLVL", shlvl, 0);
	free(shlvl);
}

void	init_null_env(t_minishell *minishell)
{
	char	*pwd;

	if (minishell->env == NULL)
	{
		pwd = getcwd(NULL, 0);
		if (pwd)
			update_var_env(&minishell->env, "PWD", pwd, 0);
		free(pwd);
		update_var_env(&minishell->env, "SHLVL", "1", 0);
	}
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
	update_shell_level(&minishell);
	init_null_env(&minishell);
	while (1)
		display_prompt(&minishell);
}
