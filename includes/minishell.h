/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:25:04 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/25 15:33:43 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <signal.h>
# include <errno.h>   
# include "libft.h"
# include "tokens.h"
# include "tokenization.h"
# include "m_signals.h"
# include "ast.h"

typedef struct s_minishell
{
	t_cmd_part		*cmd_tokens;
	t_token_type	cmd_token_last;
	t_ast_node		*ast_root;
	char			**env;
}	t_minishell;

typedef struct s_cmd_exec
{
	char	*og_text;
	char	*full_cmd;
	char	**cmd_n_args;
	char	*path;
	char	**paths;
	char	*right_path;
	int		cmd_perm;
}	t_cmd_exec;

// EXPAND VARS

int		is_valid_variable_char(char c);
int		get_variable_length(const char *cmd);
int		count_quotes_to_add(const char *var_content);
char	*replace_variables(const char *cmd);

// SPLIT ARGS

char	**split_args(char *line);


// shell

void	display_prompt(int *stop, t_minishell *minishell);


// ERR

void	other_error(char *err);
void	unexpected_token_error(t_token_type token, char *text);
void	incomplete_cmd_error(void);
void	cmd_not_found(char *cmd);
void	permission_denied(char *path, char *cmd);


// tokenize

int		add_token_last(t_token_type token, char *text, t_minishell *minishell);
int		add_token(t_token_type token, char *text, t_cmd_part **last);
void	clean_tokenized_cmd(t_minishell *minishell);
void	print_token_list(t_minishell *minishell);
char	*get_token(t_token_type token);

int		tokenize(char **rl, t_minishell *minishell);
void	clean_tokenized_cmd(t_minishell *minishell);

int		verify_tokens(t_minishell *minishell);


// CREATE AST
int cmd_to_tree(t_cmd_part *cmd, t_minishell *minishell);

// EXECUTE

int		exec_cmd(t_ast_node *command, t_minishell *minishell);
void	execute_ast(t_minishell *minishell);


#endif
