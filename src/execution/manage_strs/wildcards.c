/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:43:22 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/04 17:11:35 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	normal_next_word(t_cor_infos *cor)
{
	int	is_sq;
	int	is_dq;

	is_sq = 0;
	is_dq = 0;
	cor->i--;
	while (cor->cmd[++cor->i])
	{
		if (cor->cmd[cor->i] == ' ' && !is_sq && !is_dq)
			break ;
		else if (cor->cmd[cor->i] == '"' && !is_sq)
			is_dq = !is_dq;
		else if (cor->cmd[cor->i] == '\'' && !is_dq)
			is_sq = !is_sq;
		if (cor->new_str)
		{
			cor->new_str[*cor->n] = cor->cmd[cor->i];
		}
		(*cor->n)++;
	}
}

int	pattern_next_word(t_cor_infos *c)
{
	char	*replacement;
	char	*pattern;
	int		i;

	i = -1;
	pattern = ft_substr_rmq((char *)c->cmd, c->i, arg_len((char *)c->cmd, c->i));
	if (!pattern)
		return (-1);
	//replacement = ft_strdup("TEST RANDOM");
	replacement = concat_wildcard(pattern);
	free(pattern);
	if (!replacement)
		return (-1);
	while (replacement[++i])
	{
		if (c->new_str)
			c->new_str[*c->n] = replacement[i];
		(*c->n)++;
	}
	free(replacement);
	c->last_res++;
	c->i += arg_real_len((char *)c->cmd, c->i);
	return (0);
}

static int	count_or_rep_itt_wc(t_cor_infos *c)
{
	if (is_next_word_wildcard((char *)c->cmd, c->i))
	{
		if (pattern_next_word(c) == -1)
			return (-1);
	}
	else
		normal_next_word(c);
	return (0);
}

int	count_or_replace_wc(const char *cmd, char *new_str, int *n, int *wc_amount)
{
	t_cor_infos	cor;

	cor.i = 0;
	cor.is_sq = 0;
	cor.is_dq = 0;
	cor.n = n;
	cor.cmd = cmd;
	cor.new_str = new_str;
	cor.last_res = 0;
	while (cmd[cor.i])
	{
		while (ft_isspace(cmd[cor.i]))
			cor.i++;
		if (count_or_rep_itt_wc(&cor) == -1)
			return (-1);
		if (cor.new_str)
			cor.new_str[*cor.n] = ' ';
		(*cor.n)++;
	}
	*wc_amount = cor.last_res;
	return (0);
}

char	*replace_wildcards(char *cmd)
{
	int		n;
	int		wc_amount;
	char	*new_str;

	n = 0;
	new_str = NULL;
	if (count_or_replace_wc(cmd, new_str, &n, &wc_amount) == -1)
		return (cmd);
	if (wc_amount == 0)
		return (cmd);
	new_str = malloc((n + 1) * sizeof(char));
	n = 0;
	if (count_or_replace_wc(cmd, new_str, &n, &wc_amount) == -1)
		return (free(new_str),
			cmd);
	new_str[n] = '\0';
	return (new_str);
}
