/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:30:28 by agantaum          #+#    #+#             */
/*   Updated: 2025/02/19 17:01:58 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_token(t_token_type token)
{
	static char tokens[15][20] = {"PAREN_OPEN", "PAREN_CLOSE", "PIPE", "AND", "OR", "REDIRECT_OUT", "REDIRECT_OUT_APPEND", "REDIRECT_IN", "HERE_DOC", "COMMAND", "END_VAL", "FILE_R", "NEW_L", "AMPERSTAND"};

	return (tokens[(int)token]);
}

t_ast_node  *new_tree(void)
{
    t_ast_node *tree;

    tree = malloc(sizeof(t_ast_node));
    if (tree == NULL)
        return (NULL);
    tree->child_left = NULL;
    tree->child_right = NULL;
    tree->parent = NULL;
    tree->text = NULL;
    tree->token = NULL_TOKEN;
    return (tree);
}

t_ast_node  *new_tkn_node(t_token_type	token)
{
    t_ast_node *node;

    node = new_tree();
    if (node == NULL)
        return (NULL);
    node->token = token;
    return (node);
}
void printf_tree(t_ast_node *tree, int niveau) 
{
    int i;

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
    ft_printf("--| %s\n\n", get_token(tree->token));
    printf_tree(tree->child_left, niveau + 1);
}

int fill_tree(t_ast_node  *tree, t_cmd_part *cmd, int depth)
{
    t_ast_node  *n_parent;
    
    if (cmd == NULL)
        return (1);
    if (cmd->token == PAREN_OPEN)
        return (fill_tree(tree, cmd->next, depth - 1));
    else if (cmd->token == PAREN_CLOSE)
        return (fill_tree(tree, cmd->next, depth + 1));
    else if (cmd->token == COMMAND)
    {
        tree->token = cmd->token;
        tree->text = cmd->text;
        if (cmd->next == NULL)
            return (1);
        if (tree->parent == NULL)
        {
            n_parent = new_tkn_node(cmd->next->token);
            if (n_parent == NULL)
                return (0);
            n_parent->child_left = tree;
            tree->parent = n_parent;
            return (fill_tree(tree->parent, cmd->next, depth));
        }
        return (fill_tree(tree->parent, cmd, depth));
    }
    else if (cmd->token == REDIRECT_OUT || cmd->token == REDIRECT_OUT_APPEND
        || cmd->token == REDIRECT_IN || cmd->token == HERE_DOC)
    {
        if (tree->token = NULL_TOKEN)
        {
            tree = new_tkn_node(cmd->token);
            if (tree == NULL)
                return (0);
        }
        tree->text = cmd->text;
        if (tree->parent == NULL)
        {
            n_parent = new_tkn_node(cmd->next->token);
            if (n_parent == NULL)
                return (0);
            n_parent->child_left = tree;
            tree->parent = n_parent;
        }
        fill_tree(tree->parent, cmd->next, depth);
    }
    else if (tree->token == PIPE || tree->token == OR || cmd->token == AND)
    {
        if (cmd->token != tree->token)
            ft_printf("u fucked up\n");
        if (tree->child_right == NULL)
            fill_tree(tree->child_right, cmd->next, depth);
        if (tree->parent == NULL)
        {
            n_parent = new_tkn_node(cmd->next->token);
            if (n_parent == NULL)
                return (0);
            n_parent->child_left = tree;
            tree->parent = n_parent;
        }
        fill_tree(tree->parent, cmd->next, depth);
    }
}

int main(void)
{
    t_ast_node *tree;

    tree = new_tree();
    if (tree == NULL)
        return (0);
    // fill_tree(tree, cmd, 0);
    printf_tree(tree, -1);
    return (1);
}