/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:10:24 by agantaum          #+#    #+#             */
/*   Updated: 2025/03/10 14:15:50 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**construct_env(t_list_env *env)
{
	t_list_env	*envt;
	char		**res;
	int			i;

	i = 0;
	envt = env;
	while (envt)
	{
		envt = envt->next;
		i++;
	}
	res = malloc(sizeof(char *) * (i + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (env)
	{
		envt = env;
		res[i] = env->variable;
		env = env->next;
		free(envt);
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	*get_env_variable(t_list_env *env, char *var_name)
{
	int	i;

	while (env)
	{
		i = is_same_variable(env->variable, var_name);
		if (i)
			return (&env->variable[i]);
		env = env->next;
	}
	return (NULL);
}

void	del_env_var(t_list_env **env, char *var_name)
{
	t_list_env	*temp;
	t_list_env	*last;
	int			i;

	temp = *env;
	last = NULL;
	while (temp)
	{
		i = is_same_variable(temp->variable, var_name);
		if (i)
		{
			if (last)
				last->next = temp->next;
			else
				*env = temp->next;
			free(temp->variable);
			free(temp);
			return ;
		}
		last = temp;
		temp = temp->next;
	}
}
