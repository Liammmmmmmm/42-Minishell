/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_token_list2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:32:49 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/24 10:29:33 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	tget_a(t_cmd_part *cmd_part)
{
	if (!cmd_part)
		return (NULL_TOKEN);
	return (cmd_part->token);
}

t_token_type	tget_p(t_cmd_part *cmd_part)
{
	if (!cmd_part)
		return (NULL_TOKEN);
	return (tget_a(cmd_part->previous));
}

t_token_type	tget_n(t_cmd_part *cmd_part)
{
	if (!cmd_part)
		return (NULL_TOKEN);
	return (tget_a(cmd_part->next));
}

char	*sget_a(t_cmd_part *cmd_part)
{
	if (!cmd_part)
		return (NULL);
	return (cmd_part->text);
}

char	*sget_n(t_cmd_part *cmd_part)
{
	if (!cmd_part)
		return (NULL);
	return (sget_a(cmd_part->next));
}
