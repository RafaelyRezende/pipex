/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 08:45:07 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/09/16 19:21:18 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"

int	ft_process_split(t_env *this, t_cmd *current, char **envp)
{
	int	process_id;

	pipe(current->pipe_fd);
	process_id = fork();
	if (process_id == -1)
		ft_err_fork(this);
	else if (process_id == 0)
	{
		if (!current->prev)
		{
			if (dup2(this->file_fd[INFILE_FD], STDIN_FILENO) == -1)
				ft_cleanup_error("dup", this);
			if (dup2(current->pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
				ft_cleanup_error("dup", this);
			ft_close_all(this, current);
		}
		else
			ft_process_cmd2cmd(this, current);
		if (current->cmd_path != NULL && execve(current->cmd_path, current->cmd_split, envp) == -1)
			ft_cleanup_error("exec", this);
	}
	if (!current->prev)
		close(this->file_fd[INFILE_FD]);
	close(current->pipe_fd[WRITE_END]);
	return (process_id);
}

int	ft_process_finisher(t_env *this, t_cmd *current, char **envp)
{
	int	process_id;

	process_id = fork();
	if (process_id == -1)
		ft_cleanup_error("dup", this);
	else if (process_id == 0)
	{
		if (dup2(this->file_fd[OUTFILE_FD], STDOUT_FILENO) == -1)
			ft_cleanup_error("dup", this);
		if (dup2(current->prev->pipe_fd[READ_END], STDIN_FILENO) == -1)
			ft_cleanup_error("dup", this);
		ft_close_all(this, current);
		if (current->cmd_path != NULL && execve(current->cmd_path, current->cmd_split, envp) == -1)
			ft_cleanup_error("exec", this);
	}
	close(current->pipe_fd[WRITE_END]);
	close(current->prev->pipe_fd[READ_END]);
	return (process_id);
}

void	ft_process_cmd2cmd(t_env *this, t_cmd *current)
{
	if (dup2(current->pipe_fd[READ_END], STDIN_FILENO) == -1)
		ft_cleanup_error("dup", this);
	if (dup2(current->pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
		ft_cleanup_error("dup", this);
	ft_close_all(this, current);
}

void	ft_close_all(t_env *this, t_cmd *current)
{

	if (this->file_fd[INFILE_FD])
		close(this->file_fd[INFILE_FD]);
	if (this->file_fd[OUTFILE_FD])
		close(this->file_fd[OUTFILE_FD]);
	if (current->pipe_fd[READ_END])
		close(current->pipe_fd[READ_END]);
	if (current->pipe_fd[WRITE_END])
		close(current->pipe_fd[WRITE_END]);
}
