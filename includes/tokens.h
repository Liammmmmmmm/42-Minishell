/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:58:22 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/18 12:03:59 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

/** 
 * Liste des tokens possibles a parser
 * 
 * Pas besoin de gerer les variables, c'est plus simple de directement les remplacer
 * au moment du parsing sinon on va pas s'y retrouver
 * example con, `$> $USER` nous donne lilefebv: command not found ce qui signifie
 * qu'il remplace la variable, puis la stock comme une commande puis execute
 * 
 * Attention faut penser a pas remplacer si l'argument est entre single quote
 * 
 * le managment des single et double quote doit pas se faire qu'au niveau des arguments
 * mais a tous les points :
 * `$> '$USER'`
 * `$USER: command not found`
 * 
 * `$> "$USER   aaa"`
 * `lilefebv   aaa: command not found`
 */
typedef enum e_token_type
{
	PARENTHESIS,
	PAREN_OPEN,				/* (										*/
	PAREN_CLOSE,			/* )										*/
	PIPE,					/* |										*/
	AND,					/* &&										*/
	OR,						/* ||										*/
	REDIRECT_OUT,			/* >										*/
	REDIRECT_OUT_APPEND,	/* >>										*/
	REDIRECT_IN,			/* <										*/
	HERE_DOC,				/* <<										*/
	END_VAL,				/* Val to end <<							*/
	FILE_R,					/* A file (for <, >, >>)					*/
	COMMAND,				/* executable name (with or without path)	*/
	ARG,					/* arguments avec managment de "" et '		*/
	NEW_L					/* \n										*/
}	t_token_type;

int		is_valid_command(const char *cmd);

#endif
