/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:58:22 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/12 10:19:54 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                                  TOKENS                                  ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

/** 
 * Liste des tokens possibles a parser
 */
typedef enum e_token_type
{
	PAREN_OPEN,				/* (										*/
	PAREN_CLOSE,			/* )										*/
	PIPE,					/* |										*/
	AND,					/* &&										*/
	OR,						/* ||										*/
	REDIRECT_OUT,			/* >										*/
	REDIRECT_OUT_APPEND,	/* >>										*/
	REDIRECT_IN,			/* <										*/
	HERE_DOC,				/* <<										*/
	COMMAND,				/* executable name with his args			*/
	FILE_R,					/* Text of a redirector (filename for ex)	*/
	NEW_L,					/* \n										*/
	AMPERSTAND,				/* &										*/
	NULL_TOKEN
}	t_token_type;

/**
 * Verify if a command have valid parenthesis and quotes
 * 
 * @return -1 if the command is completly impossible
 *         0 if it can be possible if completed
 *         1 if it is correct
 * 		   -2 if cmd is null
 */
int		is_valid_command(const char *cmd);

#endif
