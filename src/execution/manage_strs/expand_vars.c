/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:58:57 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/26 15:33:57 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_variable(const char *cmd, char *new_str, int *i, int *n)
{
	char	*var_content;
	char	*var_name;
	int		var_name_length;

	var_name_length = get_variable_length(cmd + *i + 1);
	var_name = malloc((var_name_length + 1) * sizeof(char));
	if (!var_name)
		return (-1);
	ft_strlcpy(var_name, cmd + *i + 1, var_name_length + 1);
	var_content = getenv(var_name);
	*i += var_name_length + 1;
	if (new_str == NULL)
		*n += ft_sstrlen(var_content) + count_quotes_to_add(var_content);
	else
		copy_var_and_quotes(var_content, new_str, n);
	free(var_name);
	return (0);
}

int	copy_var_dq(const char *cmd, char *new_str, int *i, int *n)
{
	char	*var_content;
	char	*var_name;
	int		y;

	y = get_variable_length(cmd + *i + 1);
	var_name = malloc((y + 1) * sizeof(char));
	if (!var_name)
		return (-1);
	ft_strlcpy(var_name, cmd + *i + 1, y + 1);
	var_content = getenv(var_name);
	*i += y + 1;
	if (new_str == NULL)
		*n += ft_sstrlen(var_content);
	else
	{
		if (var_content == NULL)
			return (free(var_name), 0);
		y = -1;
		while (var_content[++y])
			new_str[(*n)++] = var_content[y];
	}
	free(var_name);
	return (0);
}

static int	count_or_rep_itt(t_cor_infos *c)
{
	if (c->cmd[c->i] == '"')
		c->is_dq = !c->is_dq;
	if (c->cmd[c->i] == '\'' && !c->is_dq)
		c->is_sq = !c->is_sq;
	if (c->cmd[c->i] == '$'
		&& is_valid_var_char(c->cmd[c->i + 1]) && !c->is_sq && c->is_dq)
	{
		if (copy_var_dq(c->cmd, c->new_str, &c->i, c->n) == -1)
			return (-1);
	}
	else if (c->cmd[c->i] == '$'
		&& is_valid_var_char(c->cmd[c->i + 1]) && !c->is_sq)
	{
		if (copy_variable(c->cmd, c->new_str, &c->i, c->n) == -1)
			return (-1);
	}
	else
	{
		if (c->new_str)
			c->new_str[*c->n] = c->cmd[c->i];
		c->i++;
		(*c->n)++;
	}
	return (0);
}

int	count_or_replace(const char *cmd, char *new_str, int *n)
{
	t_cor_infos	cor;

	cor.i = 0;
	cor.is_sq = 0;
	cor.is_dq = 0;
	cor.n = n;
	cor.cmd = cmd;
	cor.new_str = new_str;
	while (cmd[cor.i])
	{
		if (count_or_rep_itt(&cor) == -1)
			return (-1);
	}
	return (0);
}

char	*replace_variables(const char *cmd)
{
	int		n;
	char	*new_str;

	n = 0;
	new_str = NULL;
	if (count_or_replace(cmd, new_str, &n) == -1)
		return (NULL);
	new_str = malloc((n + 1) * sizeof(char));
	n = 0;
	if (count_or_replace(cmd, new_str, &n) == -1)
		return (free(new_str), NULL);
	new_str[n] = '\0';
	return (new_str);
}
