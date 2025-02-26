/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:27:02 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/17 17:27:45 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_variable_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	get_variable_length(const char *cmd)
{
	int	i;

	i = 0;
	while (is_valid_variable_char(cmd[i]))
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
