/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:31:18 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/12 09:52:00 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "tokens.h"
# include "tokenization.h"

typedef struct s_ast_node	t_ast_node;

typedef struct s_ast_node
{
	t_token_type	token;
	char			*text;
	t_ast_node		*parent;
	t_ast_node		*child_left;
	t_ast_node		*child_right;
	int				cmd_res;
	pid_t			pid;
}	t_ast_node;

/**
 * @brief Turn a flag for error in the ats and return NULL
 *
 * @param flag flag to turn off.
 */
void		*flag_off(int *flag);

/**
 * @brief Return input text or "(nil)""
 *
 * @param str the string to test.
 */
char		*null_or_txt(char *str);

/**
 * @brief Assure that the node have a parent
 *
 * 		Test if there is a parent or create one if needed.
 * 		Return 0 in case of error, and 1 for succes.
 * @param tree the node which need a parent.
 */
int			check_parent(t_ast_node *tree);

/**
 * @brief Print the tree in parameter
 *
 * Printf every node of a tree from everywhere
 * 
 * @param tree the tree to print.
 * @param level need to be at -1 for the function to work;
 */
void		printf_tree(t_ast_node *tree, int level);

/**
 * @brief Copy tree2 into tree
 * 
 * @param tree the tree to recive the tree2.
 * @param tree2 the dta for the first tree;
 */
void		cpy_tree(t_ast_node *tree, t_ast_node *tree2);

/**
 * @brief insert a node
 * 
 * Insert n_node to the right child of the tree node
 * 
 * @param tree the tree to recive the n_node.
 * @param n_node The node to insert after tree;
 */
void		insert_node(t_ast_node *tree, t_ast_node *n_node);

/**
 * @brief Return a pointer to a allocated NULL node for a ast tree
 */
t_ast_node	*new_node(void);

/**
 * @brief Return a pointer to the top of a tree
 *
 * @param tree the tree which last parent is needed.
 */
t_ast_node	*go_up_tree(t_ast_node *tree);

/**
 * @brief Create a tree from a chained list of token that represent a command
 * 
 * Use recursiv call to create a tree from a chained list of cmd and text,
 * take into acocunt the priority, can handle (),|,||,&&, <<, <, >, >>
 * 
 * Return NULL of zhere it stopped during the building of the tree
 * 
 * @param tree the new tree.
 * @param cmd the current command chained list to turn into ast;
 * @param flag error flag;
 */
t_cmd_part	*fill_tree(t_ast_node *tree, t_cmd_part *cmd, int *flag);
/**
 * @brief Manage the pipe node during ast building
 * 
 * Needed during tree creation to act in the right way when a pipe is present
 * 
 * @param tree the current tree.
 * @param cmd the current command chained list to turn into ast;
 * @param flag error flag;
 */
t_cmd_part	*manage_pipe(t_ast_node *tree, t_cmd_part *cmd, int *flag);
/**
 * @brief Manage the open parenthesis node during ast building
 * 
 * Needed during tree creation to act in the right way when a
 * open parenthesis is present
 * 
 * @param tree the current tree.
 * @param cmd the current command chained list to turn into ast;
 * @param flag error flag;
 */
t_cmd_part	*manage_open(t_ast_node *tree, t_cmd_part *cmd, int *flag);
/**
 * @brief Manage the NULL node during ast building
 * 
 * Needed during tree creation to act in the right way when a
 * NULL node is present
 * 
 * @param tree the current tree.
 * @param cmd the current command chained list to turn into ast;
 * @param flag error flag;
 */
t_cmd_part	*manage_nnode(t_ast_node *tree, t_cmd_part *cmd, int *flag);
/**
 * @brief Manage the OR and AND node during ast building
 * 
 * Needed during tree creation to act in the right way when a
 * the OR or the AND node is present
 * 
 * @param tree the current tree.
 * @param cmd the current command chained list to turn into ast;
 * @param flag error flag;
 */
t_cmd_part	*manage_orand(t_ast_node *tree, t_cmd_part *cmd, int *flag);
/**
 * @brief Manage the redicetion node during ast building
 * 
 * Needed during tree creation to act in the right way when a
 * redirection node is present
 * 
 * @param tree the current tree.
 * @param cmd the current command chained list to turn into ast;
 * @param flag error flag;
 */
t_cmd_part	*manage_redirect(t_ast_node *tree, t_cmd_part *cmd, int *flag);

#endif
