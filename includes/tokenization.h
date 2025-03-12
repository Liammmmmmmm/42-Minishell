/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:41:53 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/12 10:15:20 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "tokens.h"

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                               TOKENIZATION                               ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

typedef struct s_cmd_part	t_cmd_part;

typedef struct s_cmd_part
{
	t_token_type	token;
	char			*text;
	t_cmd_part		*previous;
	t_cmd_part		*next;
}	t_cmd_part;

/**
 * @brief Get the token type of the cmd_part given
 */
t_token_type	tget_a(t_cmd_part *cmd_part);

/**
 * @brief Get the token type of the token next cmd_part given
 */
t_token_type	tget_p(t_cmd_part *cmd_part);

/**
 * @brief Get the token type of the token before cmd_part given
 */
t_token_type	tget_n(t_cmd_part *cmd_part);

/**
 * @brief Get the text of the token next cmd_part given
 */
char			*sget_n(t_cmd_part *cmd_part);

/**
 * @brief Is the given token an operator token ?
 */
int				is_op_t(t_token_type token);

/**
 * @brief Is the given token a redirector token ?
 */
int				is_redir_t(t_token_type token);

#endif
