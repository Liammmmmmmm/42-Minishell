/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:53:49 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/10 15:49:51 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bubble_sort_tab(char **tab, int n)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	if (n <= 1)
		return ;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (case_insensitive_cmp(tab[j], tab[j + 1]) > 0)
			{
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	*tab_to_str(char *result, char **tab)
{
	size_t	total_length;
	int		i;

	i = 0;
	total_length = 1;
	while (tab[i] != NULL)
	{
		total_length += ft_sstrlen(tab[i]) + 2;
		ft_strcat(result, " ");
		ft_strcat(result, tab[i]);
		free(tab[i]);
		i++;
	}
	return (result);
}

static char	*try_open(DIR **dir, char *result)
{
	*dir = opendir(".");
	if (!*dir)
	{
		perror("opendir");
		return (NULL);
	}
	result = malloc(1);
	if (!result)
	{
		perror("malloc");
		closedir(*dir);
		return (NULL);
	}
	result[0] = '\0';
	return (result);
}

char	*concat_wildcard(const char *pattern)
{
	DIR		*dir;
	char	*result;
	char	**tab;

	dir = NULL;
	result = NULL;
	if (try_open(&dir, result) == NULL)
		return (NULL);
	result = wildcard_loop(result, dir, pattern);
	if (result == NULL)
		return (NULL);
	if (result[0] == '\0')
		return (ft_strdup(pattern));
	tab = ft_split(result, " ");
	if (tab == NULL)
	{
		perror("malloc");
		closedir(dir);
		return (NULL);
	}
	bubble_sort_tab(tab, char_tab_len(tab));
	result[0] = '\0';
	result = tab_to_str(result, tab);
	free(tab);
	return (result);
}
