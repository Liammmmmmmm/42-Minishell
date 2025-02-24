/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:52:08 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/24 15:16:48 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"

int	count_tabs(char *line, int i)
{
	int	res;
	int	is_new_word;
	int	is_sq;
	int	is_dq;

	res = 0;
	i = -1;
	is_new_word = 1;
	is_sq = 0;
	is_dq = 0;
	while (line[++i])
	{
		if (line[i] == '"' && !is_sq)
			is_dq = !is_dq;
		else if (line[i] == '\'' && !is_dq)
			is_sq = !is_sq;
		else if ((line[i] == ' ' && !is_sq && !is_dq) && is_new_word == 0)
			is_new_word = 1;
		else if ((line[i] != ' ' || is_sq || is_dq) && is_new_word == 1)
		{
			is_new_word = 0;
			res++;
		}
	}
	return (res);
}

int	arg_len(char *line, int i)
{
	int	res;
	int	is_sq;
	int	is_dq;

	res = 0;
	is_sq = 0;
	is_dq = 0;
	i--;
	while (line[++i])
	{
		if (line[i] == ' ' && !is_sq && !is_dq)
			break ;
		else if (line[i] == '"' && !is_sq)
			is_dq = !is_dq;
		else if (line[i] == '\'' && !is_dq)
			is_sq = !is_sq;
		else
			res++;
	}
	return (res);
}

// char	**split_args(char *line)
// {
// 	char	**res;

// 	res = malloc(sizeof(char *) * (count_tabs(line, 0) + 1));
// 	while ()
// }

// int	main(int argc, char **argv)
// {
// 	printf("%s, %d\n", argv[1], arg_len(argv[1], 0));
// }

/*

TEST ZARB :
lilefebv@z4r10p6:~/Documents/cursus/Minishell/42-Minishell$ export test="ok '       "ok"        ok ' -n"
lilefebv@z4r10p6:~/Documents/cursus/Minishell/42-Minishell$ echo $test
ok ' ok ok ' -n



*/