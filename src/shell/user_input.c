/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:29:19 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/18 15:52:29 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_until_complete(char **rl)
{
	int		is_valid_synax;
	char	*second_line;

	*rl = readline("mishell$ ");
	is_valid_synax = is_valid_command(*rl);
	while (is_valid_synax != 1)
	{
		if (is_valid_synax == -1)
			return (unexpected_token_error(PAREN_CLOSE),
				free(*rl), -1);
		else if (is_valid_synax == 0)
		{
			second_line = readline("> ");
			*rl = ft_strjoin_free(*rl, second_line, "\n");
			if (rl == NULL)
				return (other_error("malloc failed"), -1);
			is_valid_synax = is_valid_command(*rl);
		}
	}
	return (1);
}

void	display_prompt(int *stop, t_minishell *minishell)
{
	char	*rl;

	rl = NULL;
	if (read_until_complete(&rl) == -1)
		return ;
	if (tokenize(&rl, minishell) == -1) // appeller avant le add history car il peut lui meme ajouter des truc dans la rl si c'est pas complet
		return ;
	add_history(rl);
	printf("Command : %s\n", rl);
	if (ft_strncmp(rl, "exit", 5) == 0)
		*stop = 1;
	clean_tokenized_cmd(minishell);
	free(rl);
}

/*

Attention, le truc pour continuer a prendre l'input ne fonctionne ici que pour
si y'a pas le bon nb de parentheses ou de quotes. Si par ex une commande finie par
&&, et est donc pas encore valid il faudra gerer le fait de continuer a lire
apres la tokenization

*/
