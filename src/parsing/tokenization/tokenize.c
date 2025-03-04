/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:00:30 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/04 12:26:13 by lilefebv         ###   ########lyon.fr   */
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

int	add_fantom_cmd(t_minishell *minishell)
{
	t_cmd_part	*node;

	node = minishell->cmd_tokens;
	while (node)
	{
	//	printf("%s <- %s\n", get_token(tget_p(node)), get_token(tget_a(node)));
		if (is_redir_t(tget_a(node)) && !is_redir_t(tget_p(node)) && tget_p(node) != COMMAND && tget_p(node) != FILE_R)
		{
	//		printf("j'ajoute\n");	
			if (add_token_mid(COMMAND, NULL, &node, minishell) == -1)
				return (0);
		}
		node = node->next;
	}
	return (1);
}

int	tokenize(char **rl, t_minishell *minishell)
{
	if (line_to_tokens(*rl, minishell) == -1)
		return (-1);
	if (add_fantom_cmd(minishell) == -1)
	{
		clean_tokenized_cmd(minishell);
		return (-1);
	}
	return (1);
}
