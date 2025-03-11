/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:45:25 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/11 13:15:06 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_num(char *nb)
{
	int	i;

	i = 0;
	while (ft_isspace(nb[i]))
		i++;
	if (nb[i] == '-' || nb[i] == '+')
		i++;
	if (!ft_isdigit(nb[i]))
	{
		printf("minishell: exit: %s: numeric argument required\n", nb);
		return (0);
	}
	while (ft_isdigit(nb[i]))
		i++;
	while (ft_isspace(nb[i]))
		i++;
	if (nb[i])
	{
		printf("minishell: exit: %s: numeric argument required\n", nb);
		return (0);
	}
	return (1);
}

static unsigned int	atoui_secure(char *nb)
{
	unsigned long	res;
	int				sign;
	int				i;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(nb[i]))
		i++;
	if (nb[i] == '-')
		sign = -sign;
	if (nb[i] == '-' || nb[i] == '+')
		i++;
	while (ft_isdigit(nb[i]))
	{
		res = res * 10 + nb[i] - '0';
		if ((res - 1 > __INT64_MAX__ && sign == -1)
			|| (res > __INT64_MAX__ && sign == 1))
		{
			printf("minishell: exit: %s: numeric argument required\n", nb);
			return (2);
		}
		i++;
	}
	return (res * sign);
}

int	exit_bc(t_minishell *minishell, t_cmd_exec *cmd)
{
	unsigned int	res;
	int				num_error;

	res = 0;
	num_error = 0;
	printf("See you later !\n");
	if (cmd->cmd_n_args[1])
	{
		if (is_valid_num(cmd->cmd_n_args[1]) == 0)
		{
			num_error = 1;
			res = 2;
		}
		else
			res = atoui_secure(cmd->cmd_n_args[1]);
	}
	if (cmd->cmd_n_args[1] && cmd->cmd_n_args[2] && !num_error)
		ft_dprintf(2, "minishell: exit: too many arguments\n");
	else if (!cmd->cmd_n_args[1] || (cmd->cmd_n_args[1] && !cmd->cmd_n_args[2]))
	{
		free_cmd(cmd);
		free_exit(minishell, res);
	}
	free_cmd(cmd);
	return (1);
}

int	exit_eof(t_minishell *minishell)
{
	printf("See you later !\n");
	free_exit(minishell, 130);
	return (1);
}
