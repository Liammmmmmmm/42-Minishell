/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:43:39 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/06 15:02:33 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = -1;

void	signal_handler_here_doc(int signum)
{
	g_signal = signum;
	if (signum == SIGINT)
	{
		close(STDIN_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		// write(1, "\n", 1);
	}
}

void	signal_handler(int signum)
{

	g_signal = signum;
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay(); // TODO regler une petite couille qu'il y a avec l'historique
	}
	// <3 TODO va aussi falloir que ca se charge de kill tous les childs, et faut aussi gerer differament pendant les here doc : faut faire la meme + clear les tokens
}

void	init_sighandler(void)
{
	signal(SIGINT, signal_handler);
}

// Faire un sighandler custom pour le here doc. le here donc on dup la sortie standard et on la close pour exit direct 