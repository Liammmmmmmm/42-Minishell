/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:27:02 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/27 16:17:15 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	get_variable_length(const char *cmd)
{
	int	i;

	i = 0;
	while (is_valid_var_char(cmd[i]))
		i++;
	return (i);
}

int	count_quotes_to_add(const char *var_content)
{
	int	i;
	int	was_space;
	int	res;

	if (var_content == NULL)
		return (0);
	i = -1;
	was_space = 1;
	res = 0;
	while (var_content[++i])
	{
		if (var_content[i] != ' ' && was_space == 1)
		{
			was_space = 0;
			res++;
		}
		else if (var_content[i] == ' ' && was_space == 0)
		{
			was_space = 1;
			res++;
		}
	}
	if (was_space == 0)
		res++;
	return (res);
}

int	copy_qmark(t_cor_infos *c, int last_res, int *i, int *n)
{
	char	*var_content;
	int		y;

	var_content = params_to_string("%d", last_res);
	*i += 2;
	if (c->new_str == NULL)
		*n += ft_sstrlen(var_content);
	else
	{
		if (var_content == NULL)
			return (-1);
		y = -1;
		while (var_content[++y])
			c->new_str[(*n)++] = var_content[y];
	}
	free(var_content);
	return (0);
}

void	copy_var_and_quotes(const char *var_content, char *new_str, int *n)
{
	int	i;
	int	was_space;

	if (var_content == NULL)
		return ;
	i = -1;
	was_space = 1;
	while (var_content[++i])
	{
		if (var_content[i] != ' ' && was_space == 1)
		{
			was_space = 0;
			new_str[(*n)++] = '"';
		}
		else if (var_content[i] == ' ' && was_space == 0)
		{
			was_space = 1;
			new_str[(*n)++] = '"';
		}
		new_str[(*n)++] = var_content[i];
	}
	if (was_space == 0)
		new_str[(*n)++] = '"';
}
