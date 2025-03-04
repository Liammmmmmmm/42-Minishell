/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:53:49 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/04 15:54:37 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_next_word_wildcard(char *line, int i)
{
	int	is_sq;
	int	is_dq;

	is_sq = 0;
	is_dq = 0;
	i--;
	while (line[++i])
	{
		if (line[i] == ' ' && !is_sq && !is_dq)
			return (0);
		else if (line[i] == '*' && !is_sq && !is_dq)
			return (1);
		else if (line[i] == '"' && !is_sq)
			is_dq = !is_dq;
		else if (line[i] == '\'' && !is_dq)
			is_sq = !is_sq;
	}
	return (0);
}
