/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 08:46:58 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/09/20 17:36:33 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex_bonus.h"

void	ft_parent_logic(t_cmd *current, int *prev_pipe)
{
	if (current->prev && current->prev->pipe_fd[READ_END] != -1)
	{
		close(current->prev->pipe_fd[READ_END]);
		current->prev->pipe_fd[READ_END] = -1;
		*prev_pipe = -1;
	}
	if (current->next)
	{
		close(current->pipe_fd[WRITE_END]);
		current->pipe_fd[WRITE_END] = -1;
	}
}

void	ft_finish_pipex(t_env *this, int *prev_pipe)
{
	t_cmd	*current;

	ft_close_files(this, 0);
	if (*prev_pipe != -1)
	{
		close(*prev_pipe);
		*prev_pipe = -1;
	}
	current = this->head_cmd;
	while (current)
	{
		waitpid(current->pid, &this->status, 0);
		current = current->next;
	}
	ft_cleanup_all(this);
}

void	ft_exec_child(t_env *this, t_cmd *current, char **envp, int *prev_pipe)
{
	ft_dup_handle(this, current);
	ft_close_files(this, 0);
	if (current->prev != NULL)
		close(*prev_pipe);
	if (current->next != NULL)
		ft_close_pipes(current);
	if (current->cmd_path && current->cmd_split && \
execve(current->cmd_path, current->cmd_split, envp) == -1)
		ft_err_handle(this, "execve");
}
