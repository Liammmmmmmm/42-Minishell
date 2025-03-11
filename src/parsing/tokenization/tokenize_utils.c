/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:16:52 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/11 12:17:55 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_to_next_op(char *rl, int *y)
{
	int	is_sq;
	int	is_dq;

	is_dq = 0;
	is_sq = 0;
	while (ft_strchr("()|&<>", rl[*y]) == NULL || is_sq != 0 || is_dq != 0)
	{
		if (rl[*y] == '"' && is_sq == 0)
			is_dq = !is_dq;
		else if (rl[*y] == '\'' && is_dq == 0)
			is_sq = !is_sq;
		(*y)++;
	}
}

void	move_to_next_word(char *rl, int *y)
{
	int	is_sq;
	int	is_dq;

	is_dq = 0;
	is_sq = 0;
	while (ft_strchr("()|&<> ", rl[*y]) == NULL || is_sq != 0 || is_dq != 0)
	{
		if (rl[*y] == '"' && is_sq == 0)
			is_dq = !is_dq;
		else if (rl[*y] == '\'' && is_dq == 0)
			is_sq = !is_sq;
		(*y)++;
	}
}

int	get_text(char **text, char *rl, int	*i)
{
	int	y;
	int	s_spaces;
	int	e_spaces;

	y = *i;
	move_to_next_op(rl, &y);
	s_spaces = 0;
	while (rl[*i + s_spaces] == ' ')
		s_spaces++;
	e_spaces = 0;
	while (rl[y - e_spaces - 1] == ' ')
		e_spaces++;
	if (e_spaces + s_spaces >= y - *i)
	{
		*i = y - 1;
		return (0);
	}
	*text = malloc(sizeof(char) * (y - *i + 1 - s_spaces - e_spaces));
	if (!*text)
		return (-1);
	ft_strlcpy(*text, rl + *i + s_spaces, y - *i + 1 - s_spaces - e_spaces);
	*i = y - 1;
	return (1);
}

int	get_word(char **text, char *rl, int	*i)
{
	int	y;
	int	s_spaces;
	int	e_spaces;

	y = *i;
	move_to_next_word(rl, &y);
	s_spaces = 0;
	while (rl[*i + s_spaces] == ' ')
		s_spaces++;
	e_spaces = 0;
	while (rl[y - e_spaces - 1] == ' ')
		e_spaces++;
	if (e_spaces + s_spaces >= y - *i)
	{
		*i = y - 1;
		return (0);
	}
	*text = malloc(sizeof(char) * (y - *i + 1 - s_spaces - e_spaces));
	if (!*text)
		return (-1);
	ft_strlcpy(*text, rl + *i + s_spaces, y - *i + 1 - s_spaces - e_spaces);
	*i = y - 1;
	return (1);
}
