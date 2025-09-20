/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:05:06 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/09/20 17:36:42 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex_bonus.h"

void	ft_err_handle(t_env *this, const char *str)
{
	perror(str);
	ft_cleanup_all(this);
	exit(EXIT_FAILURE);
}

void	ft_close_files(t_env *this, int scape)
{
	close(this->file_fd[INFILE_FD]);
	close(this->file_fd[OUTFILE_FD]);
	if (scape)
	{
		ft_cleanup_all(this);
		exit(1);
	}
}

void	ft_close_pipes(t_cmd *current)
{
	close(current->pipe_fd[WRITE_END]);
	close(current->pipe_fd[READ_END]);
}

void	ft_dup_handle(t_env *this, t_cmd *current)
{
	if (!current->prev)
	{
		if (dup2(this->file_fd[INFILE_FD], STDIN_FILENO) == -1)
			ft_err_handle(this, "dup");
	}
	else
	{
		if (dup2(current->prev->pipe_fd[READ_END], STDIN_FILENO) == -1)
			ft_err_handle(this, "dup");
	}
	if (!current->next)
	{
		if (dup2(this->file_fd[OUTFILE_FD], STDOUT_FILENO) == -1)
			ft_err_handle(this, "dup");
	}
	else
	{
		if (dup2(current->pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
			ft_err_handle(this, "dup");
	}
}
