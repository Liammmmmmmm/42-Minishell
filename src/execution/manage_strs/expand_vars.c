/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:58:57 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/18 11:09:05 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_var_and_quotes(const char *var_content, char *new_str, int *n)
{
	int	i;
	int	was_space;

	if (var_content == NULL)
		return ;
	i = -1;
	was_space = 1;
	while (var_content[++i])
	{
		if (var_content[i] != ' ' && was_space == 1)
		{
			was_space = 0;
			new_str[(*n)++] = '"';
		}
		else if (var_content[i] == ' ' && was_space == 0)
		{
			was_space = 1;
			new_str[(*n)++] = '"';
		}
		new_str[(*n)++] = var_content[i];
	}
	if (was_space == 0)
		new_str[(*n)++] = '"';
}

int	copy_variable(const char *cmd, char *new_str, int *i, int *n)
{
	char	*var_content;
	char	*var_name;
	int		var_name_length;

	var_name_length = get_variable_length(cmd + *i + 1);
	var_name = malloc((var_name_length + 1) * sizeof(char));
	if (!var_name)
		return (-1);
	ft_strlcpy(var_name, cmd + *i + 1, var_name_length + 1);
	var_content = getenv(var_name);
	*i += var_name_length + 1;
	if (new_str == NULL)
		*n += ft_sstrlen(var_content) + count_quotes_to_add(var_content);
	else
		copy_var_and_quotes(var_content, new_str, n);
	free(var_name);
	return (0);
}

int	count_or_replace(const char *cmd, char *new_str, int *n)
{
	int		is_sq;
	int		is_dq;
	int		i;

	i = 0;
	is_sq = 0;
	is_dq = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"')
			is_dq = !is_dq;
		if (cmd[i] == '\'' && !is_dq)
			is_sq = !is_sq;
		if (cmd[i] == '$' && is_valid_variable_char(cmd[i + 1]) && !is_sq)
		{
			if (copy_variable(cmd, new_str, &i, n) == -1)
				return (-1);
		}
		else
		{
			if (new_str)
				new_str[*n] = cmd[i];
			i++;
			(*n)++;
		}
	}
	return (0);
}

char	*replace_variables(const char *cmd)
{
	int		n;
	char	*new_str;

	n = 0;
	new_str = NULL;
	if (count_or_replace(cmd, new_str, &n) == -1)
		return (NULL);
	new_str = malloc((n + 1) * sizeof(char));
	n = 0;
	if (count_or_replace(cmd, new_str, &n) == -1)
		return (free(new_str), NULL);
	new_str[n] = '\0';
	return (new_str);
}


/*

#include <stdio.h>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		char *cmd = "'$USER'\"$HOME_test]123'$PATH'\"$PWD_$SHELL\"'$VAR_name'\"$HOME_test]123";
		char *newstr = replace_variables(cmd);
		printf("%s\n%s\n", cmd, newstr);
		free(newstr);
	}
	else
	{
		char *newstr = replace_variables(argv[1]);
		printf("%s\n%s\n", argv[1], newstr);
		free(newstr);
	}
}


output bash :
$USER]123'/home/lilefebv/bin:/home/lilefebv/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/lilefebv/.dotnet/tools'/bin/zsh'']123

output moi
'$USER'"]123'"/home/lilefebv/bin:/home/lilefebv/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/lilefebv/.dotnet/tools"'""/bin/zsh""''"]123*/