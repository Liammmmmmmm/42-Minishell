/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:58:57 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/10 17:30:57 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_variable(t_cor_infos *c, int last_res, int *i, int *n)
{
	char	*var_content;
	char	*var_name;
	int		var_name_length;

	if (c->cmd[*i + 1] == '?')
		return (copy_qmark(c, last_res, i, n));
	var_name_length = get_variable_length(c->cmd + *i + 1);
	var_name = malloc((var_name_length + 1) * sizeof(char));
	if (!var_name)
		return (-1);
	ft_strlcpy(var_name, c->cmd + *i + 1, var_name_length + 1);
	var_content = get_env_variable(c->minishell->env, var_name);
	*i += var_name_length + 1;
	if (c->new_str == NULL)
		*n += ft_sstrlen(var_content) + count_quotes_to_add(var_content);
	else
		copy_var_and_quotes(var_content, c->new_str, n);
	free(var_name);
	return (0);
}

int	copy_var_dq(t_cor_infos *c, int last_res, int *i, int *n)
{
	char	*var_content;
	char	*var_name;
	int		y;

	if (c->cmd[*i + 1] == '?')
		return (copy_qmark(c, last_res, i, n));
	y = get_variable_length(c->cmd + *i + 1);
	var_name = malloc((y + 1) * sizeof(char));
	if (!var_name)
		return (-1);
	ft_strlcpy(var_name, c->cmd + *i + 1, y + 1);
	var_content = get_env_variable(c->minishell->env, var_name);
	*i += y + 1;
	if (c->new_str == NULL)
		*n += ft_sstrlen(var_content);
	else
	{
		if (var_content == NULL)
			return (free(var_name), 0);
		y = -1;
		while (var_content[++y])
			c->new_str[(*n)++] = var_content[y];
	}
	free(var_name);
	return (0);
}

static int	count_or_rep_itt(t_cor_infos *c, int is_xprt)
{
	if (c->cmd[c->i] == '"')
		c->is_dq = !c->is_dq;
	if (c->cmd[c->i] == '\'' && !c->is_dq)
		c->is_sq = !c->is_sq;
	if (c->cmd[c->i] == '$' && (is_valid_var_char(c->cmd[c->i + 1])
			|| c->cmd[c->i + 1] == '?') && !c->is_sq && (c->is_dq || is_xprt))
	{
		if (copy_var_dq(c, c->last_res, &c->i, c->n) == -1)
			return (-1);
	}
	else if (c->cmd[c->i] == '$' && (is_valid_var_char(c->cmd[c->i + 1])
			|| c->cmd[c->i + 1] == '?') && !c->is_sq)
	{
		if (copy_variable(c, c->last_res, &c->i, c->n) == -1)
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

int	count_or_replace(t_cor_infos cor, char *new_str, int last_res, int is_xprt)
{
	int	have_varible;

	have_varible = 0;
	cor.i = -1;
	cor.is_sq = 0;
	cor.is_dq = 0;
	cor.new_str = new_str;
	cor.last_res = last_res;
	while (cor.cmd[++cor.i])
	{
		if (cor.cmd[cor.i] == '$')
			have_varible = 1;
	}
	if (have_varible == 0)
		return (-1);
	cor.i = 0;
	while (cor.cmd[cor.i])
	{
		if (count_or_rep_itt(&cor, is_xprt) == -1)
			return (-1);
	}
	return (0);
}

char	*replace_variables(t_minishell *minishell, char *cmd, int last_res,
	int is_xprt)
{
	int			n;
	char		*new_str;
	t_cor_infos	cor;

	cor.n = &n;
	cor.cmd = cmd;
	cor.minishell = minishell;
	n = 0;
	new_str = NULL;
	if (count_or_replace(cor, new_str, last_res, is_xprt) == -1)
		return (cmd);
	new_str = malloc((n + 1) * sizeof(char));
	n = 0;
	if (count_or_replace(cor, new_str, last_res, is_xprt) == -1)
		return (free(new_str),
			cmd);
	new_str[n] = '\0';
	return (new_str);
}
