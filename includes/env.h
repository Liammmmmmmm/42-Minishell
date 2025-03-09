/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:50:31 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/09 16:26:02 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_list_env
{
	char				*variable;
	int					is_exported;
	struct s_list_env	*next;
}	t_list_env;

t_list_env	*get_chain_env(char **env, int exported);
t_list_env	*add_end_env(t_list_env	*env_lst, char *var, int exported);
void		del_env_var(t_list_env **env, char *var_name);
char		*get_env_variable(t_list_env *env, char *var_name);
char		*get_env_variable(t_list_env *env, char *var_name);
int			is_same_variable(char *env_content, char *var_name);
char		**construct_env(t_list_env *env);
void		print_env(t_list_env *env);
void		print_env_export(t_list_env *env);
void		free_env(t_list_env *env);
int			update_var_env(t_list_env **env, char *var, char *value, int exported);
#endif
