/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:20:58 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/26 18:22:51 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_part	*get_cmd_bfr_redirect(t_minishell *minishell)
{
	t_cmd_part	*cmd_part;

	cmd_part = minishell->cmd_tokens;
	while (cmd_part->next != NULL)
		cmd_part = cmd_part->next;
	while (tget_a(cmd_part) != COMMAND)
	{
		if (is_op_t(tget_a(cmd_part)) || tget_a(cmd_part) == NULL_TOKEN
			|| tget_a(cmd_part) == PAREN_CLOSE
			|| tget_a(cmd_part) == PAREN_OPEN)
			return (NULL);
		cmd_part = cmd_part->previous;
	}
	return (cmd_part);
}

int	add_tok_and_incr(t_token_type token, t_minishell *minishell, int *i)
{
	(*i)++;
	return (add_token_last(token, NULL, minishell));
}

int	directly_after_redirector(char *rl, t_minishell *minishell, int *i)
{
	int		temp;
	int		res;
	char	*text;

	temp = -1;
	text = NULL;
	while (rl[*i] == ' ')
		(*i)++;
	temp = get_word(&text, rl, i);
	if (temp == -1)
		return (-1);
	if (temp != 0)
		res = add_token_last(FILE_R, text, minishell);
	else
		res = 1;
	if (res == -1)
		free(text);
	return (res);
}

int	directly_after_filer(char *rl, t_minishell *minishell, int *i)
{
	int			temp;
	int			res;
	char		*text;
	t_cmd_part	*cmd_part;

	text = NULL;
	temp = get_text(&text, rl, i);
	if (temp == -1)
		return (-1);
	if (temp != 0)
	{
		cmd_part = get_cmd_bfr_redirect(minishell);
		if (cmd_part == NULL)
			res = add_token_bfr_redic(COMMAND, text, minishell);
		else
		{
			cmd_part->text = ft_strjoin_free(cmd_part->text, text, " ");
			res = 1;
		}
	}
	else
		res = 1;
	if (res == -1)
		free(text);
	return (res);
}

int	case_text(char *rl, t_minishell *minishell, int *i)
{
	int		temp;
	int		res;
	char	*text;

	temp = -1;
	text = NULL;
	if (is_redir_t(minishell->cmd_token_last))
		res = directly_after_redirector(rl, minishell, i);
	else if (minishell->cmd_token_last == FILE_R)
		res = directly_after_filer(rl, minishell, i);
	else
	{
		temp = get_text(&text, rl, i);
		if (temp == -1)
			return (-1);
		if (temp != 0)
			res = add_token_last(COMMAND, text, minishell);
		else
			res = 1;
		if (res == -1)
			free(text);
	}
	return (res);
}
