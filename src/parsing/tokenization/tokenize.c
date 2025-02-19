/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:00:30 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/19 10:21:24 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	get_text(char **text, char *rl, int	*i)
{
	int	y;
	int	s_spaces;
	int	e_spaces;
	
	y = *i;
	while (ft_strchr("()|&<>", rl[y]) == NULL)
		y++;
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

int	line_to_tokens(char *rl, t_minishell *minishell)
{
	int				i;
	int				temp;
	int				res;
	char			*text;

	i = 0;
	temp = -1;
	text = NULL;
	minishell->cmd_token_last = PAREN_OPEN;
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
			res = add_token_last(REDIRECT_OUT_APPEND, NULL, minishell);
			i++;
		}
		else if (rl[i] == '>' && rl[i + 1] != '>')
			res = add_token_last(REDIRECT_OUT, NULL, minishell);
		else if (rl[i] == '<' && rl[i + 1] == '<')
		{
			// Aucune idée de comment ca marche ce truc
			res = add_token_last(HERE_DOC, NULL, minishell);
			i++;
		}
		else if (rl[i] == '<' && rl[i + 1] != '<')
			res = add_token_last(REDIRECT_IN, NULL, minishell);
		else
		{
			temp = get_text(&text, rl, &i);
			if (temp == -1)
				return (-1);
			if (temp != 0)
			{
				if (minishell->cmd_token_last == REDIRECT_IN || minishell->cmd_token_last == REDIRECT_OUT || minishell->cmd_token_last == REDIRECT_OUT_APPEND || minishell->cmd_token_last == HERE_DOC)
					res = add_token_last(FILE_R, text, minishell);
				else
					res = add_token_last(COMMAND, text, minishell);
			}
			else
				res = 1;
			if (res == -1)
				free(text);
		}
		i++;
		if (res == -1)
			return (-1);
	}
	return (1);
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
