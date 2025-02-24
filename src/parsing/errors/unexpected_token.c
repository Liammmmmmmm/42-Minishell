/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unexpected_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:26:59 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/24 10:57:56 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unexpected_token_error(t_token_type token, char *text)
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
	else if (token == NEW_L)
		printf("minishell: syntax error near unexpected token `newline'\n");
	else if (token == COMMAND)
		printf("minishell: syntax error near unexpected token `%s'\n", text);
}

void	incomplete_cmd_error(void)
{
	printf("minishell: incorrect or incomplete command\n");
}

void	other_error(char *err)
{
	printf("minishell: %s\n", err);
}
