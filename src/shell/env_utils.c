/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:04:57 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/11 13:20:07 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_list_env *env)
{
	t_list_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->variable);
		free(temp);
	}
}

int	is_same_variable(char *env_content, char *var_name)
{
	size_t	i;

	i = 0;
	if (!env_content || !var_name)
		return (0);
	while (var_name[i] && var_name[i] == env_content[i]
		&& env_content[i] != '=')
		i++;
	if (i == ft_sstrlen(var_name) && env_content[i] == '=')
		return (i + 1);
	else if (i == ft_sstrlen(var_name) && env_content[i] == '\0')
		return (i);
	return (0);
}

void	print_env(t_list_env *env)
{
	while (env)
	{
		if (env->variable && env->is_exported == 0)
			printf("%s\n", env->variable);
		env = env->next;
	}
}

void	print_env_export(t_list_env *env)
{
	int	i;

	while (env)
	{
		i = 0;
		while (env->variable && (env->variable)[i] && (env->variable)[i] != '=')
			i++;
		if ((env->variable)[i] == '=')
		{
			(env->variable)[i] = '\0';
			printf("declare -x %s=%s\n",
				env->variable, &((env->variable)[i + 1]));
			(env->variable)[i] = '=';
		}
		else
			printf("declare -x %s\n", env->variable);
		env = env->next;
	}
}
