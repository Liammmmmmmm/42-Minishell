/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:54:53 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/07 12:04:17 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_command_not_null(const char *cmd)
{
	int	simple_quote;
	int	double_quote;
	int	paren_open;
	int	i;

	i = -1;
	simple_quote = 0;
	double_quote = 0;
	paren_open = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '"' && !simple_quote)
			double_quote = !double_quote;
		else if (cmd[i] == '\'' && !double_quote)
			simple_quote = !simple_quote;
		else if (cmd[i] == '(' && !simple_quote && !double_quote)
			paren_open++;
		else if (cmd[i] == ')' && !simple_quote && !double_quote)
			paren_open--;
		if (paren_open == -1)
			return (unexpected_token_error(PAREN_CLOSE, NULL), -1);
	}
	if (simple_quote || double_quote || paren_open)
		return (0);
	return (1);
}

int	is_valid_command(const char *cmd)
{
	if (!cmd)
		return (-2);
	return (is_valid_command_not_null(cmd));
}
