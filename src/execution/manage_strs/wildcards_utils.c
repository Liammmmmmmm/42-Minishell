/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:53:49 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/04 17:18:29 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_next_word_wildcard(char *line, int i)
{
	int	is_sq;
	int	is_dq;

	is_sq = 0;
	is_dq = 0;
	i--;
	while (line[++i])
	{
		if (line[i] == ' ' && !is_sq && !is_dq)
			return (0);
		else if (line[i] == '*' && !is_sq && !is_dq)
			return (1);
		else if (line[i] == '"' && !is_sq)
			is_dq = !is_dq;
		else if (line[i] == '\'' && !is_dq)
			is_sq = !is_sq;
	}
	return (0);
}

int	wildcard_match(const char *pattern, const char *str) {
	if (*pattern == '\0')
		return (*str == '\0');
	if (*pattern == '*')
		return (wildcard_match(pattern + 1, str) || (*str && wildcard_match(pattern, str + 1)));
	if (*pattern == *str)
		return (wildcard_match(pattern + 1, str + 1));
	return (0);
}

char	*ft_realloc(char *str, size_t new_len)
{
	int	len_str;
	char *new_str;

	len_str = ft_sstrlen(str);
	new_str = malloc(sizeof(char) * (len_str + new_len));
	if (new_str == NULL)
	{
		free(str);
		return(NULL);
	}
	ft_memcpy(new_str, str, len_str);
	free(str);
	return (new_str);
}

char	*wildcard_loop(char *result, DIR *dir, const char *pattern)
{
	struct dirent	*entry;
	size_t			total_length;

	total_length = 1;
	entry = readdir(dir);
	while (entry != NULL) 
	{
		if (entry->d_name[0] != '.' && wildcard_match(pattern, entry->d_name))
		{
			total_length += ft_sstrlen(entry->d_name) + 2;
			result = realloc(result, total_length);
			if (!result) {
				perror("realloc");
				closedir(dir);
				return (NULL);
			}
			ft_strcat(result, " ");
			ft_strcat(result, entry->d_name);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (result);
}

char	*concat_wildcard(const char *pattern)
{
	DIR		*dir;
	char	*result;

	dir  = opendir(".");
	if (!dir) {
		perror("opendir");
		return NULL;
	}
	result = malloc(1);
	if (!result) {
		perror("malloc");
		closedir(dir);
		return NULL;
	}
	result[0] = '\0';
	result = wildcard_loop(result, dir, pattern);
	if (result == NULL)
		return (NULL);
	if (result[0] == '\0')
		return (ft_strdup(pattern));
	return (result);
}
