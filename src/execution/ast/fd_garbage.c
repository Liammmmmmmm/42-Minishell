/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_garbage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:55:30 by lilefebv          #+#    #+#             */
/*   Updated: 2025/03/10 12:14:15 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_fd_garbage(t_fd_garbage *fd_garbage)
{
	t_fd_garbage	*temp;

	while (fd_garbage)
	{
		temp = fd_garbage;
		fd_garbage = fd_garbage->next;
		close(temp->fd);
		free(temp);
	}
}

int	new_fd_garbage(t_fd_garbage **fd_garbage, int fd)
{
	t_fd_garbage	*new;
	t_fd_garbage	*temp;

	new = malloc(sizeof(t_fd_garbage));
	if (new == NULL)
	{
		perror("minishell");
		return (0);
	}
	new->fd = fd;
	new->next = NULL;
	if (*fd_garbage == NULL)
		*fd_garbage = new;
	else
	{
		temp = *fd_garbage;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (1);
}

void	del_fd_garbage(t_fd_garbage **fd_garbage, int fd)
{
	t_fd_garbage	*temp;
	t_fd_garbage	*last;

	temp = *fd_garbage;
	last = NULL;
	while (temp)
	{
		if (fd == temp->fd)
		{
			if (last)
				last->next = temp->next;
			else
				*fd_garbage = temp->next;
			close(temp->fd);
			free(temp);
			return ;
		}
		last = temp;
		temp = temp->next;
	}
}
