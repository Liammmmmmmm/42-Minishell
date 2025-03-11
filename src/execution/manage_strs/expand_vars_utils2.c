/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:46:51 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/11 11:47:02 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_var_content_dq_export(t_cor_infos *c, int *n, char *var_content)
{
	int	y;

	if (c->new_str == NULL && c->is_export == 1)
		*n += ft_sstrlen(var_content) + 2;
	else if (c->new_str == NULL && c->is_export == 0)
		*n += ft_sstrlen(var_content);
	else
	{
		y = -1;
		if (c->is_export)
			c->new_str[(*n)++] = '"';
		if (var_content)
			while (var_content[++y])
				c->new_str[(*n)++] = var_content[y];
		if (c->is_export)
			c->new_str[(*n)++] = '"';
	}
}
