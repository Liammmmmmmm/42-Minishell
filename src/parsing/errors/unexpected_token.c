/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unexpected_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:26:59 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/05 12:36:45 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unexpected_token_error(t_token_type token, char *text)
{
	if (token == PAREN_OPEN)
		printf("minishell: syntax error near unexpected token `('\n");
	else if (token == PAREN_CLOSE)
		printf("minishell: syntax error near unexpected token `)'\n");
	else if (token == PIPE)
		printf("minishell: syntax error near unexpected token `|'\n");
	else if (token == OR)
		printf("minishell: syntax error near unexpected token `||'\n");
	else if (token == AND)
		printf("minishell: syntax error near unexpected token `&&'\n");
	else if (token == AMPERSTAND)
		printf("minishell: unsupported operator `&'\n");
	else if (token == NEW_L || token == NULL_TOKEN)
		printf("minishell: syntax error near unexpected token `newline'\n");
	else if (token == COMMAND)
		printf("minishell: syntax error near unexpected token `%s'\n", text);
	return (-1);
}

// TODO toutes les erreures doivent aller dans la sortie d'erreur et pas la standard

void	free_exit(t_minishell *minishell, int ret)
{
	free_msh(minishell);
	rl_clear_history();
	exit(ret);
}

void	incomplete_cmd_error(void)
{
	printf("minishell: incorrect or incomplete command\n");
}

void	other_error(char *err)
{
	printf("minishell: %s\n", err);
}

void	cmd_not_found(char *cmd)
{
	printf("%s: command not found\n", cmd);
}

void	permission_denied(char *path, char *cmd)
{
	printf("minishell: %s/%s: Permission denied\n", path, cmd);
}

int	perror_ret(t_minishell *minishell)
{
	perror("minishell");
	minishell->last_res = 1;
	return (1);
}

void	perror_exit(t_minishell *minishell)
{
	perror("minishell");
	free_exit(minishell, 1);
}

int	perror_file(t_minishell *minishell, char *filename)
{
	printf("minishell: %s: No such file or directory\n", filename);
	minishell->last_res = 1;
	return (1);
}
