/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:25:04 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/14 11:20:50 by lilefebv         ###   ########lyon.fr   */
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
# include "env.h"

# define DEBUG 1

# define ARROW "\001\xe2\x9e\002\x9c"
# define BRACKET "\001\xe2\x9d\002\xaf"
# define CTRLD_HERE_DOC "minishell: warning: here-document at line %d delimited\
 by end-of-file (wanted `%s')\n"

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                               FD COLLECTOR                               ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

typedef struct s_fd_garbage
{
	int					fd;
	struct s_fd_garbage	*next;
}	t_fd_garbage;

/**
 * @brief Add a fd to the list of opened fd
 */
int		new_fd_garbage(t_fd_garbage **fd_garbage, int fd);

/**
 * @brief Close a fd from the list of all opened fd and clear its node
 */
void	del_fd_garbage(t_fd_garbage **fd_garbage, int fd);

/**
 * @brief Close all fd from the list of all opened fd and clear all the nodes
 */
void	clear_fd_garbage(t_fd_garbage *fd_garbage);

/**
 * Global structure that contains all the importants things of the minishell
 */
typedef struct s_minishell
{
	t_cmd_part			*cmd_tokens;
	t_token_type		cmd_token_last;
	t_ast_node			*ast_root;
	struct s_list_env	*env;
	int					last_res;
	pid_t				pid;
	int					pipe_fd[2];
	int					have_red_in;
	int					have_red_out;
	t_fd_garbage		*fd_garbage;
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

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                               EXPAND VARS                                ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

/**
 * A struct to store differents infos usefull during the expand of variables
 */
typedef struct s_cor_infos
{
	int				i;
	int				is_sq;
	int				is_dq;
	const char		*cmd;
	char			*new_str;
	int				*n;
	int				last_res;
	int				is_export;
	t_minishell		*minishell;
}	t_cor_infos;

int		is_valid_var_char(char c);
int		get_variable_length(const char *cmd);
int		count_quotes_to_add(const char *var_content);
int		copy_qmark(t_cor_infos *c, int last_res, int *i, int *n);
void	copy_var_and_quotes(const char *var_content, char *new_str, int *n);
void	copy_var_content_dq_export(t_cor_infos *c, int *n, char *var_content);

/**
 * @brief Expand the variables
 * 
 * Take a string with variable in the format $var and replace then by their
 * content. The content of the variable can be found in the env.
 * 
 *  - A var witout any quotes is copied with cropped spaces
 * 
 *  - A var between double quotes `""` is copied as it is stored
 * 
 *  - A var between signle quotes `''` isn't expanded
 * 
 * @return The new string if variables have been replaced, and the pointer to
 *         cmd if there is no variable.
 */
char	*replace_variables(t_minishell *minishell, char *cmd, int last_res,
			int is_xprt);

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                             EXPAND WILDCARDS                             ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

char	*concat_wildcard(const char *pattern);
int		is_next_word_wildcard(char *line, int i);
int		is_next_word_wildcard(char *line, int i);
int		case_insensitive_cmp(char *s1, char *s2);
char	*wildcard_loop(char *result, DIR *dir, const char *pattern);
char	*ft_realloc(char *str, size_t new_len);
int		wildcard_match(const char *pattern, const char *str);

/**
 * @brief Expand the wildcards
 * 
 * Take a string with wildcard (*) and replace it with its matchs. Only work in
 * the current directory.
 * 
 * A wildcard wih any quotes isn't replaced.
 * 
 * @return The new string if wildcard have been replaced, and the pointer to
 *         cmd if there is no wildcard.
 */
char	*replace_wildcards(char *cmd);

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                                SPLIT ARGS                                ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

int		arg_len(char *line, int i);
int		arg_real_len(char *line, int i);
char	*ft_substr_rmq(char *line, int i, int len);

/**
 * Split a command to get a tab of strings like argv. First arg is the
 * executable, each other line of the tab is an arg.
 * 
 * It also remove the quotes it need to remove
 * 
 * @return The splitted command as a tab of strings
 */
char	**split_args(char *line);

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                                   SHELL                                  ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

/**
 * Display the minishell command input prompt and manage everything after that :
 * 
 * 1. Tokenization
 * 
 * 2. Verify if the parenthesis and quotes are valides
 * 
 * 3. Verify if the tokens list is valid (for example 2 pipes without command are
 *   rejected here)
 * 
 * 4. Get the here docs
 * 
 * 5. Build the AST
 * 
 * 6. Execute the AST
 */
void	display_prompt(t_minishell *minishell);

/**
 * Free everything and exit with the code in parameters
 */
void	free_exit(t_minishell *minishell, int ret);
void	free_msh(t_minishell *minishell);

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                                   ERRORS                                 ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

void	other_error(char *err);
void	cmd_not_found(char *cmd);
void	incomplete_cmd_error(void);
int		perror_ret(t_minishell *minishell);
void	perror_exit(t_minishell *minishell);
void	permission_denied(char *path, char *cmd);
int		free_ret(t_minishell *minishell, int ret);
int		perror_file(t_minishell *minishell, char *filename);
int		unexpected_token_error(t_token_type token, char *text);
void	permission_denied_nc(char *cmd);

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                                  TOKENIZE                                ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

/**
 * Add token to the list
 */
int		add_token(t_token_type token, char *text, t_cmd_part **last);

/**
 * Add token to the end of the list
 */
int		add_token_last(t_token_type token, char *text, t_minishell *minishell);

/**
 * Add token at any position of the list
 */
int		add_token_mid(t_token_type token, char *text, t_cmd_part **last,
			t_minishell *msh);

/**
 * Add token before the last redirector
 */
int		add_token_bfr_redic(t_token_type token, char *text, t_minishell *msh);

/**
 * Verify if the token list is valid before sending it to the AST builder
 */
int		verify_tokens(t_minishell *minishell);

/**
 * Transform the list read by readline to a token list and store it into
 * t_minishell
 */
int		tokenize(char **rl, t_minishell *minishell);

/**
 * Free the token list
 */
void	clean_tokenized_cmd(t_minishell *minishell);

/**
 * List of multiples utils for the tokenize function
 */

void	move_to_next_op(char *rl, int *y);
void	move_to_next_word(char *rl, int *y);
int		get_word(char **text, char *rl, int	*i);
int		get_text(char **text, char *rl, int	*i);
int		case_text(char *rl, t_minishell *minishell, int *i);
int		directly_after_filer(char *rl, t_minishell *minishell, int *i);
int		directly_after_redirector(char *rl, t_minishell *minishell, int *i);
int		add_tok_and_incr(t_token_type token, t_minishell *minishell, int *i);

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                                    AST                                   ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

/**
 * Takes a tokenized command and transform it into an AST, before storing it
 * into t_minishell.
 */
int		cmd_to_tree(t_cmd_part *cmd, t_minishell *minishell);

/**
 * Free the AST.
 */
void	free_tree(t_minishell *minishell);

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                                 EXECUTION                                ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

int		char_tab_len(char **tab);
void	free_cmd(t_cmd_exec *cmd);
int		is_cmd_export(char *cmd_text);
int		manage_null_cmd(t_minishell *minishell);
void	find_right_path(t_cmd_exec *cmd);

/**
 * Take a node and call a different function depending of the token type :
 * 
 * - `AND` : exec_and_or(..., ..., 1);
 * 
 * - `OR` : exec_and_or(..., ..., 0);
 * 
 * - `PIPE` : exec_pipe(..., ...);
 * 
 * - `REDIRECT_IN`, `REDIRECT_OUT`, `REDIRECT_OUT_APPEND`, `HERE_DOC` :
 *   exec_redirect(..., ...);
 * 
 * - `COMMAND` : exec_cmd(..., ...);
 */
int		recursive_tree_read(t_minishell *minishell, t_ast_node *node);

/**
 * If we have a pipe, create a fork to start the two side of the pipe at the
 * same time, and link them with a pipe.
 */
int		exec_pipe(t_minishell *minishell, t_ast_node *node);

/**
 * Change the output or input by the file stored in the redirector.
 */
int		exec_redirect(t_minishell *minishell, t_ast_node *node);

/**
 * Exec one side of the tree, and execute the other side or not depending of
 * the result of the other side and `is_and`
 */
int		exec_and_or(t_minishell *minishell, t_ast_node *node, int is_and);

/**
 * Before executing a command, this one make all the necessary to prepare it.
 * 
 * - Replace the variables
 * 
 * - Replace the wildcards
 * 
 * - Split the args
 * 
 * - Search for the command and if we can execute it
 */
int		init_cmd_exec(t_cmd_exec *cmd, char *cmd_text, t_minishell *minishell);

/**
 * Execute a command if every infos given on the init are correct.
 */
int		exec_cmd(t_ast_node *command, t_minishell *minishell);

/**
 * @return 1 if the command is one of the builtins, 0 otherwise.
 */
int		is_builtins(t_cmd_exec *cmd);

/**
 * Special exec command function dedicated to the builtins -> do not use
 * execve and 
 */
int		exec_builtins(t_minishell *minishell, t_cmd_exec *cmd);

/**
 * Take an AST and execute it correctly : apply the redirections, execute the
 * pipes, parenthesis execution order, AND & OR executed according to the
 * result of the precedent command, ...
 */
void	execute_ast(t_minishell *minishell);

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                                   DEBUG                                  ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

char	*get_token(t_token_type token);
void	print_token_list(t_minishell *minishell);

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                                 HERE DOC                                 ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

/**
 * Get all here doc, create them and let the user fill them.
 */
int		all_here_doc(t_minishell *minishell);

/**
 * Destroy the here docs created from the start
 */
void	unlink_here_doc(t_minishell *minishell);

/**
 * Destroy the here docs created from an error point
 */
int		unlink_here_doc_error(t_cmd_part *cmd_p);

/**
 * Free a here doc
 */
void	free_hd(t_cmd_part	*cmd_p, char *filename, int fd);

/**
 * Generate a unique name for the here doc
 */
char	*gen_hd_name(void);

/**
 * Remove the quotes we need to remove to get the delimiter. (If the delimiter
 * is for example `"|"`, the real delimiter isn't `"|"` anymore but `|`)
 */
void	rm_quotes(char *delimiter);

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                                 BUILTINS                                 ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

int		cd_bc(t_minishell *minishell, t_cmd_exec *cmd);
int		env_bc(t_minishell *minishell, t_cmd_exec *cmd);
int		pwd_bc(t_minishell *minishell, t_cmd_exec *cmd);
int		echo_bc(t_minishell *minishell, t_cmd_exec *cmd);
int		exit_bc(t_minishell *minishell, t_cmd_exec *cmd);
int		unset_bc(t_minishell *minishell, t_cmd_exec *cmd);
int		export_bc(t_minishell *minishell, t_cmd_exec *cmd);
int		exit_eof(t_minishell *minishell);

#endif
