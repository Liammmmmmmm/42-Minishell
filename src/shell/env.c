/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:05:21 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/10 14:10:42 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_env	*new_env_var(char *var, int exported)
{
	t_list_env	*new;

	new = malloc(sizeof(t_list_env));
	if (new == NULL)
	{
		perror("minishell");
		return (NULL);
	}
	new->variable = ft_strdup(var);
	new->next = NULL;
	new->is_exported = exported;
	return (new);
}

t_list_env	*add_end_env(t_list_env *env_lst, char *var, int exported)
{
	if (env_lst == NULL)
		return (new_env_var(var, exported));
	if (env_lst->next == NULL)
		env_lst->next = add_end_env(env_lst->next, var, exported);
	else
		add_end_env(env_lst->next, var, exported);
	return (env_lst);
}

t_list_env	*get_chain_env(char **env, int exported)
{
	int			i;
	t_list_env	*env_lst;

	i = 0;
	env_lst = NULL;
	while (env[i])
	{
		env_lst = add_end_env(env_lst, env[i], exported);
		i++;
	}
	return (env_lst);
}

int	update_var_env(t_list_env **env, char *var, char *value, int exported)
{
	char	*new_value;

	del_env_var(env, var);
	new_value = malloc((ft_sstrlen(var) + ft_sstrlen(value) + 2)
			* sizeof(char));
	if (new_value == NULL)
	{
		perror("minishell");
		return (1);
	}
	ft_strlcpy(new_value, var, ft_sstrlen(var) + 1);
	if (value)
	{
		new_value[ft_sstrlen(var)] = '=';
		ft_strlcpy(new_value + ft_sstrlen(var) + 1,
			value, ft_sstrlen(value) + 1);
	}
	*env = add_end_env(*env, new_value, exported);
	free(new_value);
	return (0);
}
