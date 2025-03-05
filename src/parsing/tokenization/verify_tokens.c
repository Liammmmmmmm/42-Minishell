/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:19:04 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/05 15:29:48 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_op_t(t_token_type token)
{
	if (token == PIPE || token == OR || token == AND)
		return (1);
	return (0);
}

int	is_op_or_pc_t(t_token_type token)
{
	if (is_op_t(token) || token == PAREN_CLOSE)
		return (1);
	return (0);
}

int	is_redir_t(t_token_type token)
{
	if (token == REDIRECT_IN || token == REDIRECT_OUT
		|| token == REDIRECT_OUT_APPEND || token == HERE_DOC)
		return (1);
	return (0);
}

static int	verify_token_itt(t_cmd_part *cmd_part)
{
	if (!cmd_part->previous)
		if (is_op_t(tget_a(cmd_part)))
			return (unexpected_token_error(tget_a(cmd_part), NULL));
	if (!cmd_part->next)
		if (is_op_t(tget_a(cmd_part)))
			return (incomplete_cmd_error(), -1);
	if (tget_a(cmd_part) == AMPERSTAND)
		return (unexpected_token_error(AMPERSTAND, NULL));
	if (is_op_t(tget_a(cmd_part)) && (is_op_or_pc_t(tget_n(cmd_part)) || tget_n(cmd_part) == NULL_TOKEN))
		return (unexpected_token_error(tget_n(cmd_part), NULL));
	if (tget_a(cmd_part) == PAREN_OPEN && tget_n(cmd_part) != COMMAND
		&& !is_redir_t(tget_n(cmd_part)))
		return (unexpected_token_error(tget_n(cmd_part), sget_n(cmd_part)));
	if (tget_a(cmd_part) == PAREN_CLOSE && tget_n(cmd_part) != NULL_TOKEN
		&& !is_op_t(tget_n(cmd_part)) && !is_redir_t(tget_n(cmd_part)))
		return (unexpected_token_error(tget_n(cmd_part), sget_n(cmd_part)));
	if ((!is_op_t(tget_a(cmd_part)) && tget_a(cmd_part) != NULL_TOKEN)
		&& tget_n(cmd_part) == PAREN_OPEN)
		return (unexpected_token_error(tget_n(cmd_part), NULL));
	if (is_redir_t(tget_a(cmd_part)) && (tget_n(cmd_part) == NULL_TOKEN
			|| is_op_or_pc_t(tget_n(cmd_part))))
		return (unexpected_token_error(tget_n(cmd_part), NULL));
	if (tget_a(cmd_part) == HERE_DOC && tget_n(cmd_part) != FILE_R)
		return (unexpected_token_error(tget_n(cmd_part), NULL));
	
	return (0);
}

int	verify_tokens(t_minishell *minishell)
{
	t_cmd_part	*cmd_part;

	cmd_part = minishell->cmd_tokens;
	if (!cmd_part)
		return (-1);
	while (cmd_part)
	{
		if (verify_token_itt(cmd_part) == -1)
			return (-1);
		cmd_part = cmd_part->next;
	}
	return (1);
}
