/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:43:39 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/07 15:39:42 by lilefebv         ###   ########lyon.fr   */
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
		printf("\n");
		rl_on_new_line();
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
	else if (signum == SIGSEGV)
		printf("minishell: Segmentation fault\n");
	else if (signum == SIGPIPE)
		printf("minishell: Broken pipe\n");
}

void	init_sighandler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	signal(SIGSEGV, signal_handler);
	signal(SIGPIPE, signal_handler);
}
