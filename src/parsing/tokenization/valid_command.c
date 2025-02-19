/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:54:53 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/19 10:50:31 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Verifie si une commande envoyée est est correcte (en terme du nombre de quote
 * ouvertes/fermées (single et double), et de parentheses).
 * 
 * @return -1 if the command is completly impossible
 *         0 if it can be possible if completed
 *         1 if it is correct
 */
int	is_valid_command(const char *cmd)
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
