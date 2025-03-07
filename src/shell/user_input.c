/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:29:19 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/07 12:01:19 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_until_complete(char **rl, t_minishell *minishell)
{
	int		is_valid;

	*rl = readline("mishell$ ");
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
	// print_token_list(minishell);
	if (verify_tokens(minishell) == 1)
	{
		if (g_signal == SIGINT)
			minishell->last_res = 130;
		g_signal = -1;
		if (all_here_doc(minishell) == -1)
			return (clean_tokenized_cmd(minishell));
		print_token_list(minishell);
		// printf("\nCommand : %s\n\n", rl);
		if (cmd_to_tree(minishell->cmd_tokens, minishell) == 1)
		{
			minishell->ast_root = go_up_tree(minishell->ast_root);
			printf_tree(minishell->ast_root, -1);
			signal(SIGINT, signal_handler_execution);
			execute_ast(minishell);
			free_tree(minishell);
		}
		else
			ft_dprintf(2, "minishell: AST build error.\n");
		unlink_here_doc(minishell);
	}
	else
		print_token_list(minishell);
	clean_tokenized_cmd(minishell);
	free(rl);
}
