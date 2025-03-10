/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:29:19 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/10 16:00:43 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_folder_only(t_minishell *minishell)
{
	char	*res;

	res = ft_strrchr(get_env_variable(minishell->env, "PWD"), '/');
	if (res[1])
		return (res + 1);
	else
		return (res);
}

char	*get_prompt(t_minishell *minishell)
{
	char	*ret;
	char	*user;
	char	*pwd;

	user = get_env_variable(minishell->env, "USER");
	pwd = get_env_variable(minishell->env, "PWD");
	ret = NULL;
	if (user && pwd && user[0] && pwd[0])
	{
		if (minishell->last_res == 0)
			ret = params_to_string(GREEN"➜ "BLUE"["BRIGHT_CYAN"%s"BLUE"]"YELLOW
					BOLD" %s "BRIGHT_PURPLE"❯ "NC,
					get_env_variable(minishell->env, "USER"),
					get_folder_only(minishell));
		else
			ret = params_to_string(RED"➜ "BLUE"["BRIGHT_CYAN"%s"BLUE"]"YELLOW
					BOLD" %s "BRIGHT_PURPLE"❯ "NC,
					get_env_variable(minishell->env, "USER"),
					get_folder_only(minishell));
	}
	return (ret);
}

int	read_until_complete(char **rl, t_minishell *minishell)
{
	int			is_valid;
	const char	default_err[47] = RED"➜"CYAN" minishell "BRIGHT_PURPLE"❯ "NC;
	char		*prompt;

	prompt = get_prompt(minishell);
	if (prompt)
		*rl = readline(prompt);
	else
		*rl = readline(default_err);
	free(prompt);
	is_valid = is_valid_command(*rl);
	if (is_valid == -2)
		exit_eof(minishell);
	if (is_valid <= 0)
	{
		free(*rl);
		minishell->last_res = 2;
		incomplete_cmd_error();
		return (-1);
	}
	return (1);
}

int	continue_token_valid(t_minishell *minishell)
{
	if (g_signal == SIGINT)
		minishell->last_res = 130;
	g_signal = -1;
	if (all_here_doc(minishell) == -1)
	{
		clean_tokenized_cmd(minishell);
		return (-1);
	}
	if (cmd_to_tree(minishell->cmd_tokens, minishell) == 1)
	{
		minishell->ast_root = go_up_tree(minishell->ast_root);
		signal(SIGINT, signal_handler_execution);
		execute_ast(minishell);
		free_tree(minishell);
	}
	else
		ft_dprintf(2, "minishell: AST build error.\n");
	unlink_here_doc(minishell);
	return (0);
}

void	display_prompt(t_minishell *minishell)
{
	char	*rl;

	init_sighandler();
	if (g_signal == SIGINT)
		minishell->last_res = 130;
	g_signal = -1;
	rl = NULL;
	if (read_until_complete(&rl, minishell) == -1)
		return ;
	add_history(rl);
	if (tokenize(&rl, minishell) == -1)
		return ;
	if (verify_tokens(minishell) == 1)
	{
		if (continue_token_valid(minishell) == -1)
			return ;
	}
	clean_tokenized_cmd(minishell);
	free(rl);
}
