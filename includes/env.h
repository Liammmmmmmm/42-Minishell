/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:50:31 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/12 10:08:45 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                                   ENV                                    ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

typedef struct s_list_env
{
	char				*variable;
	int					is_exported;
	struct s_list_env	*next;
}	t_list_env;

/**
 * @brief Take a string tab env and transform it into a t_list_env
 * 
 * @param env The env you want to transform
 * @param exported Set the value of is_exported
 * 
 * @return Your env as a linked list
 */
t_list_env	*get_chain_env(char **env, int exported);

/**
 * @brief Adds an environment variable to the end
 *
 * This function adds a new environment variable to the end of the list.
 *
 * @param env_lst The env as a linked list
 * @param var The full variable (name=content or name)
 * @param exported is_exported value of the node
 * 
 * @return The pointer to the first element of the list
 */
t_list_env	*add_end_env(t_list_env	*env_lst, char *var, int exported);

/**
 * @brief Deletes an environment variable
 *
 * @param env The env as a linked list
 * @param var_name The name of the variable to delete
 */
void		del_env_var(t_list_env **env, char *var_name);

/**
 * @brief Gets an environment variable
 *
 * This function retrieves the value of an environment variable.
 * You cant free the pointer returned.
 * 
 * @param env The env as a linked list
 * @param var_name The name of the variable to retrieve
 * 
 * @return The value of the environment variable, or NULL if not found
 */
char		*get_env_variable(t_list_env *env, char *var_name);

/**
 * @brief Constructs the environment
 *
 * This function constructs the environment from a given list of variables.
 * It is the inverse of the get_chained_env function. It also free the linked
 * list.
 *
 * @param env The actual env as a linked list
 * 
 * @return A pointer to the constructed environment
 */
char		**construct_env(t_list_env *env);

/**
 * @brief Frees the environment variables
 *
 * This function releases the memory allocated for the environment variables.
 * 
 * @param env The env to free
 */
void		free_env(t_list_env *env);

/**
 * @brief Updates an environment variable
 *
 * This function updates the value of an existing environment variable.
 *
 * @param env The env as a linked list
 * @param var The name of the variable to update
 * @param value The new value to set for the variable
 * @param exprt is_exported value of the node
 * 
 * @return 0 on success, 1 on failure
 */
int			update_var_env(t_list_env **env, char *var, char *value, int exprt);

int			is_same_variable(char *env_content, char *var_name);
void		print_env(t_list_env *env);
void		print_env_export(t_list_env *env);

#endif
