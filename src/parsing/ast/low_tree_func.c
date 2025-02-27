/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   low_tree_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:33:53 by agantaum          #+#    #+#             */
/*   Updated: 2025/02/27 10:29:12 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*go_up_tree(t_ast_node *tree)
{
	if (tree == NULL)
		return (NULL);
	if (tree->parent == NULL)
		return (tree);
	else
		return (go_up_tree(tree->parent));
}

void	free_tree_rec(t_ast_node *tree)
{
	if (tree != NULL)
	{
		free_tree_rec(tree->child_left);
		free_tree_rec(tree->child_right);
		// if (tree != NULL && tree->text != NULL)
		// 	free(tree->text);
		free(tree);
	}
}

void	free_tree(t_ast_node *tree)
{
	while (tree->parent)
		tree = tree->parent;
	free_tree_rec(tree);
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
	tree->pid = -1;
	return (tree);
}

char	*null_or_txt(char *str)
{
	if (str == NULL)
		return ("(nil)");
	else
		return (str);
}

void	printf_tree(t_ast_node *tree, int niveau)
{
	int	i;

	i = -1;
	if (tree == NULL)
	{
		while (++i < niveau)
			ft_printf("        ");
		ft_printf("--| (nil)\n\n");
		return ;
	}
	if (niveau == -1 && tree->parent == NULL)
		niveau = 0;
	if (niveau == -1)
		return (printf_tree(tree->parent, niveau));
	printf_tree(tree->child_right, niveau + 1);
	while (++i < niveau)
		ft_printf("        ");
	ft_printf("--| %s txt %s\n\n", get_token(tree->token), \
		null_or_txt(tree->text));
	printf_tree(tree->child_left, niveau + 1);
}
