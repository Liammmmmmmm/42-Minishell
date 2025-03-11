/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:52:08 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/11 12:31:26 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tabs(char *line, int i)
{
	int	res;
	int	is_new_word;
	int	is_sq;
	int	is_dq;

	res = 0;
	i = -1;
	is_new_word = 1;
	is_sq = 0;
	is_dq = 0;
	while (line[++i])
	{
		if (line[i] == '"' && !is_sq)
			is_dq = !is_dq;
		else if (line[i] == '\'' && !is_dq)
			is_sq = !is_sq;
		else if ((line[i] == ' ' && !is_sq && !is_dq) && is_new_word == 0)
			is_new_word = 1;
		else if ((line[i] != ' ' || is_sq || is_dq) && is_new_word == 1)
		{
			is_new_word = 0;
			res++;
		}
	}
	return (res);
}

int	arg_len(char *line, int i)
{
	int	res;
	int	is_sq;
	int	is_dq;

	res = 0;
	is_sq = 0;
	is_dq = 0;
	i--;
	while (line[++i])
	{
		if (line[i] == ' ' && !is_sq && !is_dq)
			break ;
		else if (line[i] == '"' && !is_sq)
			is_dq = !is_dq;
		else if (line[i] == '\'' && !is_dq)
			is_sq = !is_sq;
		else
			res++;
	}
	return (res);
}

int	arg_real_len(char *line, int i)
{
	int	res;
	int	is_sq;
	int	is_dq;

	res = 0;
	is_sq = 0;
	is_dq = 0;
	i--;
	while (line[++i])
	{
		if (line[i] == ' ' && !is_sq && !is_dq)
			break ;
		else
		{
			if (line[i] == '"' && !is_sq)
				is_dq = !is_dq;
			else if (line[i] == '\'' && !is_dq)
				is_sq = !is_sq;
			res++;
		}
	}
	return (res);
}

char	*ft_substr_rmq(char *line, int i, int len)
{
	int		y;
	int		is_sq;
	int		is_dq;
	char	*res;

	y = 0;
	is_sq = 0;
	is_dq = 0;
	i--;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (line[++i])
	{
		if (line[i] == ' ' && !is_sq && !is_dq)
			break ;
		else if (line[i] == '"' && !is_sq)
			is_dq = !is_dq;
		else if (line[i] == '\'' && !is_dq)
			is_sq = !is_sq;
		else
			res[y++] = line[i];
	}
	res[y++] = 0;
	return (res);
}

char	**split_args(char *line)
{
	char	**res;
	int		i;
	int		y;
	int		tabs;
	int		argl;

	y = -1;
	i = 0;
	tabs = count_tabs(line, 0);
	res = malloc(sizeof(char *) * (tabs + 1));
	if (!res)
		return (NULL);
	while (++y < tabs)
	{
		while (ft_isspace(line[i]))
			i++;
		argl = arg_real_len(line, i);
		res[y] = ft_substr_rmq(line, i, arg_len(line, i));
		if (!res[y])
			return (res);
		i += argl;
	}
	res[y] = NULL;
	return (res);
}
