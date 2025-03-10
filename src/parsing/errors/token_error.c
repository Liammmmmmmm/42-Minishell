/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:26:59 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/10 14:15:37 by lilefebv         ###   ########lyon.fr   */
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
		ft_dprintf(2,
			"minishell: syntax error near unexpected token `newline'\n");
	else if (token == COMMAND)
		ft_dprintf(2,
			"minishell: syntax error near unexpected token `%s'\n", text);
	return (-1);
}

void	incomplete_cmd_error(void)
{
	ft_dprintf(2, "minishell: incorrect or incomplete command\n");
}

void	other_error(char *err)
{
	ft_dprintf(2, "minishell: %s\n", err);
}
