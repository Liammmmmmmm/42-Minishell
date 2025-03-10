/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:58:22 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/10 13:40:220 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

/** 
 * Liste des tokens possibles a parser
 * 
 * Pas besoin de gerer les variables,
 * c'est plus simple de directement les remplacer
 * au moment du parsing sinon on va pas s'y retrouver
 * example, `$> $USER` nous donne lilefebv: command not found ce qui signifie
 * qu'il remplace la variable, puis la stock comme une commande puis execute
 * 
 * Attention faut penser a pas remplacer si l'argument est entre single quote
 * 
 * le managment des single et
 * double quote doit pas se faire qu'au niveau des arguments
 * mais a tous les points :
 * `$> '$USER'`
 * `$USER: command not found`
 * 
 * `$> "$USER   aaa"`
 * `lilefebv   aaa: command not found`
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
	COMMAND,				/* executable name (with or without path)	*/
	END_VAL,				/* Val to end <<							*/
	FILE_R,					
	NEW_L,					/* \n										*/
	AMPERSTAND,
	NULL_TOKEN
}	t_token_type;

/**
 * Verifie si une commande envoyée est est correcte (en terme du nombre de quote
 * ouvertes/fermées (single et double), et de parentheses).
 * 
 * @return -1 if the command is completly impossible
 *         0 if it can be possible if completed
 *         1 if it is correct
 * 		   -2 if cmd is null
 */
int		is_valid_command(const char *cmd);

#endif
