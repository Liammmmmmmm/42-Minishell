/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:00:30 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/18 16:54:30 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_token(t_token_type token, char *text, t_cmd_part **last)
{
	t_cmd_part	*new_node;

	new_node = malloc(sizeof(t_cmd_part));
	if (!new_node)
		return (-1);
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

int	add_token_last(t_token_type token, char *text, t_minishell *minishell)
{
	static t_cmd_part	*cmd_part = NULL;

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

int	get_text(char **text, char *rl, int	i)
{
	int	y;
	
	y = i;
	while (ft_strchr("()|&<>", rl[y]) == NULL)
		y++;
	*text = malloc(sizeof(char) * (y - i + 1));
	if (!*text)
		return (-1);
	ft_strlcpy(*text, rl + i, y - i + 1);
	return (y - i - 1);
}

int	line_to_tokens(char *rl, t_minishell *minishell)
{
	int		i;
	int		temp;
	int		res;
	char	*text;

	i = 0;
	temp = -1;
	text = NULL;
	while (rl[i])
	{
		if (rl[i] == '(')
			res = add_token_last(PAREN_OPEN, NULL, minishell);
		else if (rl[i] == ')')
			res = add_token_last(PAREN_CLOSE, NULL, minishell);
		else if (rl[i] == '|' && rl[i + 1] == '|')
		{
			res = add_token_last(OR, NULL, minishell);
			i++;
		}
		else if (rl[i] == '|' && rl[i + 1] != '|')
			res = add_token_last(PIPE, NULL, minishell);
		else if (rl[i] == '&' && rl[i + 1] == '&')
		{
			res = add_token_last(AND, NULL, minishell);
			i++;
		}
		else if (rl[i] == '&' && rl[i + 1] != '&')
			res = add_token_last(AMPERSTAND, NULL, minishell);
		else if (rl[i] == '>' && rl[i + 1] == '>')
		{
			// RECUP AUSSI LE TEXT
			res = add_token_last(REDIRECT_OUT_APPEND, NULL, minishell);
			i++;
		}
		else if (rl[i] == '>' && rl[i + 1] != '>')
		{
			// RECUP AUSSI LE TEXT
			res = add_token_last(REDIRECT_OUT, NULL, minishell);
		}
		else if (rl[i] == '<' && rl[i + 1] == '<')
		{
			// Aucune idée de comment ca marche ce truc
			res = add_token_last(HERE_DOC, NULL, minishell);
			i++;
		}
		else if (rl[i] == '<' && rl[i + 1] != '<')
		{
			// RECUP AUSSI LE TEXT
			res = add_token_last(REDIRECT_IN, NULL, minishell);
		}
		else
		{
			temp = get_text(&text, rl, i);
			if (temp == -1)
				return (-1);
			i += temp;
			res = add_token_last(COMMAND, text, minishell);
			if (res == -1)
				free(text);
		}
		i++;
		if (res == -1)
			return (-1);
	}
	return (1);
}

char	*get_token(t_token_type token)
{
	static char tokens[15][20] = {"PAREN_OPEN", "PAREN_CLOSE", "PIPE", "AND", "OR", "REDIRECT_OUT", "REDIRECT_OUT_APPEND", "REDIRECT_IN", "HERE_DOC", "COMMAND", "END_VAL", "NEW_L", "AMPERSTAND"};

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
		free(cmd_temp);
	}
	minishell->cmd_tokens = NULL;
}

int	tokenize(char **rl, t_minishell *minishell)
{
	if (line_to_tokens(*rl, minishell) == -1)
		return (-1);
	print_token_list(minishell);
	// appel a line_to_token
	// boucle while sur les verifs qui sort si la commande est plus valide ou si elle est fini qui permet de completer tant qu'on continue
	return (1);
}
