/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unexpected_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:26:59 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/06 14:51:11 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unexpected_token_error(t_token_type token, char *text)
{
	if (token == PAREN_OPEN)
		ft_dprintf(2, "minishell: syntax error near unexpected token `('\n");
	else if (token == PAREN_CLOSE)
		ft_dprintf(2, "minishell: syntax error near unexpected token `)'\n");
	else if (token == PIPE)
		ft_dprintf(2, "minishell: syntax error near unexpected token `|'\n");
	else if (token == OR)
		ft_dprintf(2, "minishell: syntax error near unexpected token `||'\n");
	else if (token == AND)
		ft_dprintf(2, "minishell: syntax error near unexpected token `&&'\n");
	else if (token == AMPERSTAND)
		ft_dprintf(2, "minishell: unsupported operator `&'\n");
	else if (token == NEW_L || token == NULL_TOKEN)
		ft_dprintf(2, "minishell: syntax error near unexpected token `newline'\n");
	else if (token == COMMAND)
		ft_dprintf(2, "minishell: syntax error near unexpected token `%s'\n", text);
	return (-1);
}

void	free_exit(t_minishell *minishell, int ret)
{
	free_msh(minishell);
	exit(ret);
}

int	free_ret(t_minishell *minishell, int ret)
{
	free_msh(minishell);
	return (ret);
}

void	incomplete_cmd_error(void)
{
	ft_dprintf(2, "minishell: incorrect or incomplete command\n");
}

void	other_error(char *err)
{
	ft_dprintf(2, "minishell: %s\n", err);
}

void	cmd_not_found(char *cmd)
{
	ft_dprintf(2, "%s: command not found\n", cmd);
}

void	permission_denied(char *path, char *cmd)
{
	ft_dprintf(2, "minishell: %s/%s: Permission denied\n", path, cmd);
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
	ft_dprintf(2, "minishell: %s: No such file or directory\n", filename);
	minishell->last_res = 1;
	return (1);
}
