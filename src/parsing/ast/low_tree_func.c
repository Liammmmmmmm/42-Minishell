/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   low_tree_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:33:53 by agantaum          #+#    #+#             */
/*   Updated: 2025/02/25 14:19:06 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ast_node(t_ast_node *tree)
{
	if (tree != NULL && tree->text != NULL)
		free(tree->text);
	if (tree != NULL)
		free(tree);
}

void	free_tree(t_ast_node *tree)
{
	if (tree != NULL)
	{
		free_ast_node(tree->child_left);
		free_ast_node(tree->child_right);
		free_ast_node(tree);
	}
}

t_ast_node	*new_node(void)
{
	t_ast_node	*tree;

	tree = malloc(sizeof(t_ast_node));
	if (tree == NULL)
		return (NULL);
	tree->child_left = NULL;
	tree->child_right = NULL;
	tree->parent = NULL;
	tree->text = NULL;
	tree->token = NULL_TOKEN;
	tree->cmd_res = -2;
	return (tree);
}

t_ast_node  *new_tkn_node(t_token_type	token)
{
	t_ast_node	*node;

	node = new_node();
	if (node == NULL)
		return (NULL);
	node->token = token;
	return (node);
}

char *null_or_txt(char *str)
{
	if (str == NULL)
		return ("(nil)");
	else return (str);
}

void printf_tree(t_ast_node *tree, int niveau) 
{
	int	i;

	i = -1;
	if (tree == NULL)
	{
		while(++i < niveau)
			ft_printf("        ");
		ft_printf("--| (nil)\n\n");
		return ;
	}
	if (niveau == -1 && tree->parent == NULL) 
		niveau = 0;
	if (niveau == -1)
		return printf_tree(tree->parent, niveau);
	printf_tree(tree->child_right, niveau + 1);
	while(++i < niveau)
		ft_printf("        ");
	ft_printf("--| %s txt %s\n\n", get_token(tree->token), null_or_txt(tree->text));
	printf_tree(tree->child_left, niveau + 1);
}
