/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:43:39 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/07 11:46:16 by lilefebv         ###   ########lyon.fr   */
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
		printf("\n");
		rl_replace_line("", 0);
	}
}

void	signal_handler_child(int signum)
{
	g_signal = signum;
	if (signum == SIGINT)
		close(STDIN_FILENO);
}

void	signal_handler_execution(int signum)
{
	g_signal = signum;
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	signal_handler(int signum)
{
	g_signal = signum;
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_sighandler(void)
{
	signal(SIGINT, signal_handler);
}

// Faire un sighandler custom pour le here doc. le here donc on dup la sortie standard et on la close pour exit direct 