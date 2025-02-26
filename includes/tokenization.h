/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:41:53 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/26 14:06:24 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef tokenization_H
# define tokenization_H

#include "tokens.h"

typedef struct s_cmd_part	t_cmd_part;

typedef struct s_cmd_part
{
	t_token_type	token;
	char			*text;
	t_cmd_part		*previous;
	t_cmd_part		*next;
}	t_cmd_part;

t_token_type	tget_a(t_cmd_part *cmd_part);
t_token_type	tget_p(t_cmd_part *cmd_part);
t_token_type	tget_n(t_cmd_part *cmd_part);
char			*sget_n(t_cmd_part *cmd_part);

int				is_op_t(t_token_type token);
int				is_redir_t(t_token_type token);

#endif
