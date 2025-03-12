/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_signals.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:47:24 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/12 10:11:59 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_SIGNALS_H
# define M_SIGNALS_H

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                                 SIGNALS                                  ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

extern int	g_signal;

/**
 * @brief Init all signals for "normal" minishell
 */
void	init_sighandler(void);

/**
 * @brief Specific signal handler for here docs
 */
void	signal_handler_here_doc(int signum);

/**
 * @brief Specific signal handler for childs process in here doc
 */
void	signal_handler_child(int signum);

/**
 * @brief Specific signal handler for child process during execution
 */
void	signal_handler_execution(int signum);

#endif
