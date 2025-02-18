/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:25:04 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/18 10:01:07 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

// EXPAND VARS

int	is_valid_variable_char(char c);
int	get_variable_length(const char *cmd);
int	count_quotes_to_add(const char *var_content);


// shell

void	display_prompt(void);


#endif
