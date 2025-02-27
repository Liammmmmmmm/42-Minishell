/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:00:30 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/27 09:37:31 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	line_to_token_itt(char *rl, t_minishell *minishell, int *i)
{
	int	res;

	if (rl[*i] == '(')
		res = add_token_last(PAREN_OPEN, NULL, minishell);
	else if (rl[*i] == ')')
		res = add_token_last(PAREN_CLOSE, NULL, minishell);
	else if (rl[*i] == '|' && rl[*i + 1] == '|')
		res = add_tok_and_incr(OR, minishell, i);
	else if (rl[*i] == '|' && rl[*i + 1] != '|')
		res = add_token_last(PIPE, NULL, minishell);
	else if (rl[*i] == '&' && rl[*i + 1] == '&')
		res = add_tok_and_incr(AND, minishell, i);
	else if (rl[*i] == '&' && rl[*i + 1] != '&')
		res = add_token_last(AMPERSTAND, NULL, minishell);
	else if (rl[*i] == '>' && rl[*i + 1] == '>')
		res = add_tok_and_incr(REDIRECT_OUT_APPEND, minishell, i);
	else if (rl[*i] == '>' && rl[*i + 1] != '>')
		res = add_token_last(REDIRECT_OUT, NULL, minishell);
	else if (rl[*i] == '<' && rl[*i + 1] == '<')
		res = add_tok_and_incr(HERE_DOC, minishell, i);
	else if (rl[*i] == '<' && rl[*i + 1] != '<')
		res = add_token_last(REDIRECT_IN, NULL, minishell);
	else
		res = case_text(rl, minishell, i);
	return (res);
}

int	line_to_tokens(char *rl, t_minishell *minishell)
{
	int	i;

	i = 0;
	minishell->cmd_token_last = PAREN_OPEN;
	while (ft_isspace(rl[i]))
		i++;
	while (rl[i])
	{
		if (line_to_token_itt(rl, minishell, &i) == -1)
			return (-1);
		i++;
	}
	return (1);
}

int	tokenize(char **rl, t_minishell *minishell)
{
	if (line_to_tokens(*rl, minishell) == -1)
		return (-1);
	return (1);
}
