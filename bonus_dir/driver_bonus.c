/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:05:06 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/09/22 17:49:12 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex_bonus.h"

void	ft_err_handle(t_env *this, const char *str)
{
	t_cmd	*current;

	perror(str);
	current = this->head_cmd;
	while (current)
	{
		ft_close_cmd_pipes(current);
		current = current->next;
	}
	ft_close_files(this, 0);
	ft_cleanup_all(this);
	exit(EXIT_FAILURE);
}

void	ft_close_files(t_env *this, int scape)
{
	if (this->file_fd[INFILE_FD] != -1)
		close(this->file_fd[INFILE_FD]);
	if (this->file_fd[OUTFILE_FD] != -1)
		close(this->file_fd[OUTFILE_FD]);
	if (scape)
	{
		ft_cleanup_all(this);
		exit(1);
	}
}

void	ft_close_pipes(t_cmd *current)
{
	if (current->pipe_fd[WRITE_END] != -1)
		close(current->pipe_fd[WRITE_END]);
	if (current->pipe_fd[READ_END] != -1)
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
