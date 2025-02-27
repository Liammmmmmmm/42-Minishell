/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:29:19 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/27 12:27:14 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_until_complete(char **rl)
{
	int		is_valid_synax;
	char	*second_line;

	*rl = readline("mishell$ ");
	is_valid_synax = is_valid_command(*rl);
	while (is_valid_synax != 1)
	{
		if (is_valid_synax == -1)
			return (free(*rl), -1);
		else if (is_valid_synax == 0)
		{
			second_line = readline("> ");
			*rl = ft_strjoin_free(*rl, second_line, "\n");
			if (rl == NULL)
				return (other_error("malloc failed"), -1);
			is_valid_synax = is_valid_command(*rl);
		}
	}
	return (1);
}

void	display_prompt(int *stop, t_minishell *minishell)
{
	char	*rl;

	rl = NULL;
	if (read_until_complete(&rl) == -1)
		return ;
	add_history(rl);
	if (tokenize(&rl, minishell) == -1)
		return ;
	if (verify_tokens(minishell) == 1)
	{
		all_here_doc(minishell);
		print_token_list(minishell);
		printf("\nCommand : %s\n\n", rl);
		if (cmd_to_tree(minishell->cmd_tokens, minishell) == 1)
		{
			printf_tree(minishell->ast_root, -1);
			execute_ast(minishell);
			free_tree(minishell->ast_root);
		}
		else
		{
			printf("Bah jsp trop la frerot l'arbre s'est pas construit\n");
		}
	}
	else
		print_token_list(minishell);
	if (ft_strncmp(rl, "exit", 5) == 0)
		*stop = 1;
	clean_tokenized_cmd(minishell);
	free(rl);
}
