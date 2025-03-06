/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:05:21 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/06 16:27:06 by lilefebv         ###   ########lyon.fr   */
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

void	free_env()
{
	
}

int	is_same_variable(char *env_content, char *var_name)
{
	size_t	i;

	i = 0;
	while (var_name[i] && var_name[i] == env_content[i])
		i++;
	if (i == ft_sstrlen(var_name) && env_content[i] == '=')
		return (i + 1);
	return (0);
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

t_list_env	*new_env_var(char *var)
{
	t_list_env *new;

	new = malloc(sizeof(t_list_env));
	if (new == NULL)
		return (NULL);
		
	new->variable = ft_strdup(var);
	new->next = NULL;
	return (new);
}

t_list_env	*add_end_env(t_list_env *env_lst, char *var)
{
	if (env_lst == NULL)
		return (new_env_var(var));
	if (env_lst->next == NULL)
		env_lst->next = add_end_env(env_lst->next, var);
	else
		add_end_env(env_lst->next, var);
	return (env_lst);
}

t_list_env	*get_chain_env(char **env)
{
	int			i;
	t_list_env	*env_lst;
	
	i = 0;
	env_lst = NULL;
	while (env[i])
	{
		env_lst = add_end_env(env_lst, env[i]);
		i++;
	}
	return (env_lst);
}

void	print_env(t_list_env *env)
{
	while (env)
	{
		if (env->variable)
			printf("%s\n", env->variable);
		env = env->next;
	}
}
