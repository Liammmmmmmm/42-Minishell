/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:30:28 by agantaum          #+#    #+#             */
/*   Updated: 2025/02/25 15:48:34 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_part *manage_open(t_ast_node *tree, t_cmd_part *cmd)
{
    t_ast_node  *tree2;
    t_ast_node  *n_node;
    
    tree2 = new_node();
    if (tree2 == NULL)
        return (NULL);
    cmd = fill_tree(tree2, cmd, 0);
    tree2 = go_up_tree(tree2);
    if (tree2 == NULL)
        return (NULL);
    if (tree2->token == NULL_TOKEN)
    {
        tree2 = tree2->child_left;
        free(tree2->parent);
    }
    tree->child_left = tree2->child_left;
    tree->child_right = tree2->child_right;
    tree->token = tree2->token;
    tree->text = tree2->text;
    if (tree->parent == NULL)
    {
        n_node = new_node();
        if (n_node == NULL)
            return (cmd);
        n_node->child_left = tree;
        tree->parent = n_node;
    }
    free(tree2);
    return (cmd);
}

t_cmd_part  *fill_tree(t_ast_node  *tree, t_cmd_part *cmd, int depth)
{
    t_ast_node  *n_node;
    
    if (cmd == NULL || cmd->token == PAREN_CLOSE)
    {
        return (cmd);
    }
    if (tree->token == NULL_TOKEN)
    {
        if (cmd->token == PAREN_OPEN)
        {
            cmd = manage_open(tree, cmd->next);
            if (cmd == NULL)
                ft_printf("Ur fucked\n");
            return (fill_tree(tree->parent, cmd->next, depth));
        }
        else if (cmd->token == PIPE || cmd->token == OR || cmd->token == AND)
            tree->token = cmd->token;
        else if (cmd->token == COMMAND)
        {
            tree->token = cmd->token;
            tree->text = cmd->text;
        }
        else if (cmd->token == REDIRECT_IN || cmd->token == REDIRECT_OUT || cmd->token == REDIRECT_OUT_APPEND)
        {
            tree->token = cmd->token;
            tree->text = cmd->next->text;
            return (fill_tree(tree, cmd->next->next, depth));
        }
        return (fill_tree(tree, cmd->next, depth));
    }
    if (tree->token == COMMAND)
    {
        if (tree->parent == NULL)
        {
            n_node = new_node();
            if (n_node == NULL)
                return (cmd);
            n_node->child_left = tree;
            tree->parent = n_node;
        }
        return (fill_tree(tree->parent, cmd, depth));
    }
    if (tree->token == REDIRECT_IN || tree->token == REDIRECT_OUT || tree->token == REDIRECT_OUT_APPEND)
    {
        if (cmd->token == REDIRECT_IN || cmd->token == REDIRECT_OUT || cmd->token == REDIRECT_OUT_APPEND)
        {
            n_node = new_node();
            if (n_node == NULL)
                return (cmd);
            if (tree->child_left == NULL)
            {
                n_node = new_node();
                if (n_node == NULL)
                    return (cmd);
                n_node->parent = tree;
                tree->child_left = n_node;
            }
            n_node->parent = tree;
            n_node->child_left = tree->child_left;
            tree->child_left->parent = n_node;
            tree->child_left = n_node;
            return (fill_tree(tree->child_left, cmd, depth));
        }
        if (tree->parent == NULL)
        {
            n_node = new_node();
            if (n_node == NULL)
                return (cmd);
            n_node->child_left = tree;
            tree->parent = n_node;
        }
        return (fill_tree(tree->parent, cmd, depth));
    }
    if (tree->token == PIPE)
    {
        if (tree->child_right == NULL)
        {
            n_node = new_node();
            if (n_node == NULL)
                return (cmd);
            n_node->parent = tree;
            tree->child_right = n_node;
            return (fill_tree(tree->child_right, cmd, depth));
        }
        if (cmd->token == REDIRECT_IN || cmd->token == REDIRECT_OUT || cmd->token == REDIRECT_OUT_APPEND)
        {
            n_node = new_node();
            if (n_node == NULL)
                return (cmd);
            n_node->parent = tree;
            n_node->child_left = tree->child_right;
            tree->child_right->parent = n_node;
            tree->child_right = n_node;
            return (fill_tree(tree->child_right, cmd, depth));
        }
        if (tree->parent == NULL)
        {
            n_node = new_node();
            if (n_node == NULL)
                return (cmd);
            n_node->child_left = tree;
            tree->parent = n_node;
        }
        return (fill_tree(tree->parent, cmd, depth));
    }
    if (tree->token == OR || tree->token == AND)
    {
        if (tree->child_right == NULL)
        {
            n_node = new_node();
            if (n_node == NULL)
                return (cmd);
            n_node->parent = tree;
            tree->child_right = n_node;
            return (fill_tree(tree->child_right, cmd, depth));
        }
        if (cmd->token == PIPE || cmd->token == REDIRECT_IN || cmd->token == REDIRECT_OUT || cmd->token == REDIRECT_OUT_APPEND)
        {
            n_node = new_node();
            if (n_node == NULL)
                return (cmd);
            n_node->parent = tree;
            n_node->child_left = tree->child_right;
            tree->child_right->parent = n_node;
            tree->child_right = n_node;
            return (fill_tree(tree->child_right, cmd, depth));
        }
        if (tree->parent == NULL)
        {
            n_node = new_node();
            if (n_node == NULL)
                return (cmd);
            n_node->child_left = tree;
            tree->parent = n_node;
        }
        return (fill_tree(tree->parent, cmd, depth));
    }
    go_up_tree(tree);
    return (cmd);

}

int cmd_to_tree(t_cmd_part *cmd, t_minishell *minishell)
{
    t_ast_node *tree;
    
    tree = new_node();
    if (tree == NULL)
        return (-1);
    fill_tree(tree, cmd, 0);
    if (tree == NULL)
        return (-1);
    if (tree->parent != NULL && tree->parent->token == NULL_TOKEN)
    {
        free(tree->parent);
        tree->parent = NULL;
    }
    ft_printf("--------------\n");
    printf_tree(tree, -1);
    ft_printf("--------------\n");
    minishell->ast_root = tree;
    return (1);
}