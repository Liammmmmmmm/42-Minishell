/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:19:47 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/26 15:04:42 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token(t_token_type token)
{
	static char tokens[20][20] = {"PAREN_OPEN", "PAREN_CLOSE", "PIPE", "AND", "OR", "REDIRECT_OUT", "REDIRECT_OUT_APPEND", "REDIRECT_IN", "HERE_DOC", "COMMAND", "END_VAL", "FILE_R", "NEW_L", "AMPERSTAND", "NULL_TOKEN"};

	return (tokens[(int)token]);
}

void	print_token_list(t_minishell *minishell)
{
	t_cmd_part *cmd_part;

	cmd_part = minishell->cmd_tokens;
	printf("%16s %32s %16s %16s %16s\n", "Token", "Text", "Previous", "Self", "Next");
	while (cmd_part)
	{
		printf("%16s %32s %16p %16p %16p\n", get_token(cmd_part->token), cmd_part->text, cmd_part->previous, cmd_part, cmd_part->next);
		cmd_part = cmd_part->next;
	}
}

void	clean_tokenized_cmd(t_minishell *minishell)
{
	t_cmd_part *cmd_part;
	t_cmd_part *cmd_temp;

	cmd_part = minishell->cmd_tokens;
	while (cmd_part)
	{
		cmd_temp = cmd_part;
		cmd_part = cmd_part->next;
		if (cmd_temp->text)
			free(cmd_temp->text);
		free(cmd_temp);
	}
	minishell->cmd_tokens = NULL;
}

int	add_token(t_token_type token, char *text, t_cmd_part **last)
{
	t_cmd_part	*new_node;

	new_node = malloc(sizeof(t_cmd_part));
	if (!new_node)
	{
		if (text)
			free(text);
		return (-1);
	}
	new_node->next = NULL;
	new_node->text = text;
	new_node->token = token;
	if (*last == NULL)
	{
		*last = new_node;
		new_node->previous = NULL;
	}
	else
	{
		new_node->previous = *last;
		new_node->previous->next = new_node;
	}
	return (1);
}

int	add_token_mid(t_token_type token, char *text, t_cmd_part **last, t_minishell *msh)
{
	t_cmd_part	*new_node;

	new_node = malloc(sizeof(t_cmd_part));
	if (!new_node)
		return (-1);
	new_node->next = *last;
	new_node->text = text;
	new_node->token = token;
	new_node->previous = (*last)->previous;
	if ((*last)->previous)
		new_node->previous->next = new_node;
	else
	{
		msh->cmd_tokens = new_node;
		(*last)->previous = new_node;
	}
	return (1);
}

int	add_token_last(t_token_type token, char *text, t_minishell *minishell)
{
	static t_cmd_part	*cmd_part = NULL;

	minishell->cmd_token_last = token;
	if (minishell->cmd_tokens == NULL)
	{
		if (add_token(token, text, &minishell->cmd_tokens) == -1)
			return (-1);
		cmd_part = minishell->cmd_tokens;
		return (1);
	}
	else
	{
		while ((cmd_part)->next != NULL)
			cmd_part = (cmd_part)->next;
		return (add_token(token, text, &cmd_part));
	}
}

int	add_token_bfr_redic(t_token_type token, char *text, t_minishell *minishell)
{
	t_cmd_part	*cmd_part = NULL;

	cmd_part = minishell->cmd_tokens;
	while (cmd_part->next != NULL)
		cmd_part = cmd_part->next;
	while (tget_p(cmd_part) == FILE_R || is_redir_t(tget_p(cmd_part)))
		cmd_part = cmd_part->previous;
	return (add_token_mid(token, text, &cmd_part, minishell));
}
