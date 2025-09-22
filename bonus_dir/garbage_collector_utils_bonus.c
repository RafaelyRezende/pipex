/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_utils_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 08:46:01 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/09/22 17:55:43 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex_bonus.h"

void	ft_err_fork(t_env *this, t_cmd *current, int *prev_pipe)
{
	t_cmd	*tmp;

	perror("fork");
	ft_close_cmd_pipes(current);
	if (prev_pipe && *prev_pipe != -1)
		close(*prev_pipe);
	tmp = this->head_cmd;
	while (tmp && tmp != current)
	{
		ft_close_cmd_pipes(tmp);
		tmp = tmp->next;
	}
	ft_close_files(this, 1);
}

void	ft_err_dir(t_env *this)
{
	ft_putstr_fd("zsh: no such file or directory: ", 2);
	ft_putstr_fd(this->infile, 2);
	ft_putstr_fd("\n", 2);
}

void    ft_close_cmd_pipes(t_cmd *current)
{
	if (current)
	{
		if (current->pipe_fd[READ_END] != -1)
		{
			close(current->pipe_fd[READ_END]);
			current->pipe_fd[READ_END] = -1;
		}
		if (current->pipe_fd[WRITE_END] != -1)
		{
			close(current->pipe_fd[WRITE_END]);
			current->pipe_fd[WRITE_END] = -1;
		}
	}
}
