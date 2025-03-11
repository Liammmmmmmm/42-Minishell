/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:49:04 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/11 10:59:44 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token(t_token_type token)
{
	static char	tokens[20][20] = {"PAREN_OPEN", "PAREN_CLOSE", "PIPE", "AND",
		"OR", "REDIRECT_OUT", "REDIRECT_OUT_APPEND", "REDIRECT_IN", "HERE_DOC",
		"COMMAND", "END_VAL", "FILE_R", "NEW_L", "AMPERSTAND", "NULL_TOKEN"};

	return (tokens[(int)token]);
}

void	print_token_list(t_minishell *minishell)
{
	t_cmd_part	*cmd_part;

	cmd_part = minishell->cmd_tokens;
	printf("%16s %32s %16s %16s %16s\n", "Token", "Text", "Previous", "Self",
		"Next");
	while (cmd_part)
	{
		printf("%16s %32s %16p %16p %16p\n", get_token(cmd_part->token),
			cmd_part->text, cmd_part->previous, cmd_part, cmd_part->next);
		cmd_part = cmd_part->next;
	}
}

void	printf_tree(t_ast_node *tree, int level)
{
	int	i;

	i = -1;
	if (tree == NULL)
	{
		while (++i < level)
			ft_printf("        ");
		ft_printf("--| (nil)\n\n");
		return ;
	}
	if (level == -1 && tree->parent == NULL)
		level = 0;
	if (level == -1)
		return (printf_tree(tree->parent, level));
	printf_tree(tree->child_right, level + 1);
	while (++i < level)
		ft_printf("        ");
	ft_printf("--| %s txt %s\n\n", get_token(tree->token), \
		null_or_txt(tree->text));
	printf_tree(tree->child_left, level + 1);
}
