/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:25:04 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/06 12:48:43 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include <linux/limits.h>
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
	int				last_res;
	pid_t			pid;
	int				pipe_fd[2];
	int				have_red_in;
	int				have_red_out;
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
	int		status;
}	t_cmd_exec;

// EXPAND VARS

typedef struct s_cor_infos
{
	int			i;
	int			is_sq;
	int			is_dq;
	const char	*cmd;
	char		*new_str;
	int			*n;
	int			last_res;
}	t_cor_infos;

int		is_valid_var_char(char c);
int		get_variable_length(const char *cmd);
int		count_quotes_to_add(const char *var_content);
char	*replace_variables(char *cmd, int last_res);
int		copy_qmark(t_cor_infos *c, int last_res, int *i, int *n);
void	copy_var_and_quotes(const char *var_content, char *new_str, int *n);

char	*replace_wildcards(char *cmd);
char	*concat_wildcard(const char *pattern);
int		is_next_word_wildcard(char *line, int i);
// SPLIT ARGS

char	**split_args(char *line);
int		arg_len(char *line, int i);
int		arg_real_len(char *line, int i);
char	*ft_substr_rmq(char *line, int i, int len);

// shell

void	display_prompt(t_minishell *minishell);

void	free_exit(t_minishell *minishell, int ret);

// ERR

void	other_error(char *err);
void	cmd_not_found(char *cmd);
void	incomplete_cmd_error(void);
int		perror_ret(t_minishell *minishell);
void	perror_exit(t_minishell *minishell);
void	permission_denied(char *path, char *cmd);
int		free_ret(t_minishell *minishell, int ret);
int		perror_file(t_minishell *minishell, char *filename);
int		unexpected_token_error(t_token_type token, char *text);

// tokenize

void	clean_tokenized_cmd(t_minishell *minishell);
int		add_token(t_token_type token, char *text, t_cmd_part **last);
int		add_token_last(t_token_type token, char *text, t_minishell *minishell);

int		verify_tokens(t_minishell *minishell);
int		tokenize(char **rl, t_minishell *minishell);
void	clean_tokenized_cmd(t_minishell *minishell);
int		add_token_mid(t_token_type token, char *text, t_cmd_part **last,
			t_minishell *msh);
int		add_token_bfr_redic(t_token_type token, char *text, t_minishell *msh);

void	move_to_next_op(char *rl, int *y);
void	move_to_next_word(char *rl, int *y);
int		get_word(char **text, char *rl, int	*i);
int		get_text(char **text, char *rl, int	*i);
int		case_text(char *rl, t_minishell *minishell, int *i);
int		directly_after_filer(char *rl, t_minishell *minishell, int *i);
int		directly_after_redirector(char *rl, t_minishell *minishell, int *i);
int		add_tok_and_incr(t_token_type token, t_minishell *minishell, int *i);

// CREATE AST
int 	cmd_to_tree(t_cmd_part *cmd, t_minishell *minishell);
void	free_tree(t_minishell *minishell);

// EXECUTE
int		char_tab_len(char **tab);
void	free_cmd(t_cmd_exec *cmd);
void	execute_ast(t_minishell *minishell);
int		exec_pipe(t_minishell *minishell, t_ast_node *node);
int		exec_cmd(t_ast_node *command, t_minishell *minishell);
int		exec_redirect(t_minishell *minishell, t_ast_node *node);
int		recursive_tree_read(t_minishell *minishell, t_ast_node *node);
int 	exec_and_or(t_minishell *minishell, t_ast_node *node, int is_and);

// DEBUG
char	*get_token(t_token_type token);
void	print_token_list(t_minishell *minishell);


// HERE DOC
int		all_here_doc(t_minishell *minishell);


// FREEEE 
void	free_msh(t_minishell *minishell);

// BRUT CMDS
int		cd_bc(t_minishell *minishell, t_cmd_exec *cmd);
int		env_bc(t_minishell *minishell, t_cmd_exec *cmd);
int		pwd_bc(t_minishell *minishell, t_cmd_exec *cmd);
int		echo_bc(t_minishell *minishell, t_cmd_exec *cmd);
int		exit_bc(t_minishell *minishell, t_cmd_exec *cmd);
int		unset_bc(t_minishell *minishell, t_cmd_exec *cmd);
int		export_bc(t_minishell *minishell, t_cmd_exec *cmd);

// SIGNALS
void	signal_handler_here_doc(int signum);

#endif
