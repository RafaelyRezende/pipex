/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:05:06 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/09/17 17:44:52 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"

static void	ft_err_dir(t_env *this);

int	main(int argc, char **argv, char **envp)
{
	t_env	this;
	t_cmd	*current;
	int		prev_pipe_read;

	if (argc < 5)
		return (ft_error_args());
	if (ft_init_env(&this, argc, argv, envp))
		return (ft_cleanup_all(&this), -1);
	this.file_fd[INFILE_FD] = open(this.infile, O_RDONLY);
	if (this.file_fd[INFILE_FD] < 0)
		ft_err_dir(&this);
	this.file_fd[OUTFILE_FD] = open(this.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (this.file_fd[OUTFILE_FD] < 0)
		ft_err_dir(&this);
	prev_pipe_read = -1;
	current = this.head_cmd;
	while (current)
	{
		if (current->next != NULL && pipe(current->pipe_fd) == -1)
		{
			if (prev_pipe_read != -1)
				close(prev_pipe_read);
			perror("pipe");
			close(this.file_fd[INFILE_FD]);
			close(this.file_fd[OUTFILE_FD]);
			ft_cleanup_all(&this);
			exit(1);
		}
		current->pid = fork();
		if (current->pid == -1)
		{
			perror("fork");
			if (!current->next)
			{
				close(current->pipe_fd[WRITE_END]);
				close(current->pipe_fd[READ_END]);
			}
			if (prev_pipe_read != -1)
				close(prev_pipe_read);
			close(this.file_fd[INFILE_FD]);
			close(this.file_fd[OUTFILE_FD]);
			ft_cleanup_all(&this);
			exit(1);
		}
		else if (current->pid == 0) // Child process
		{
			if (!current->prev) // If first command
			{
				if (dup2(this.file_fd[INFILE_FD], STDIN_FILENO) == -1)
				{
					perror("dup");
					ft_cleanup_all(&this);
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				if (dup2(current->prev->pipe_fd[READ_END], STDIN_FILENO) == -1)
				{
					perror("dup");
					ft_cleanup_all(&this);
					exit(EXIT_FAILURE);
				}
			}
			if (!current->next) // If last command
			{
				if (dup2(this.file_fd[OUTFILE_FD], STDOUT_FILENO) == -1)
				{
					perror("dup");
					ft_cleanup_all(&this);
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				if (dup2(current->pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
				{
					perror("dup");
					ft_cleanup_all(&this);
					exit(EXIT_FAILURE);
				}
			}
			close(this.file_fd[INFILE_FD]);
			close(this.file_fd[OUTFILE_FD]);
			if (current->prev != NULL)
				close(prev_pipe_read);
			if (current->next != NULL)
			{
				close(current->pipe_fd[WRITE_END]);
				close(current->pipe_fd[READ_END]);
			}
			if (current->cmd_path && current->cmd_split && execve(current->cmd_path, current->cmd_split, envp) == -1)
			{
				perror("execve");
				ft_cleanup_all(&this);
				exit(EXIT_FAILURE);
			}
		}
		if (current->prev && current->prev->pipe_fd[READ_END] != -1)
		{
			close(current->prev->pipe_fd[READ_END]);
			current->prev->pipe_fd[READ_END] = -1;
			prev_pipe_read = -1;
		}
		if (current->next)
		{
			close(current->pipe_fd[WRITE_END]);
			current->pipe_fd[WRITE_END] = -1;
		}
		current = current->next;
	}
	close(this.file_fd[INFILE_FD]);
	close(this.file_fd[OUTFILE_FD]);
	if (prev_pipe_read != -1)
	{
		close(prev_pipe_read);
		prev_pipe_read = -1;
	}
	current = this.head_cmd;
	while (current)
	{
		waitpid(current->pid, &this.status, 0);
		current = current->next;
	}
	ft_cleanup_all(&this);
	return (WEXITSTATUS(this.status));
}

static
void	ft_err_dir(t_env *this)
{
	ft_putstr_fd("zsh: no such file or directory: ", 2);
	ft_putstr_fd(this->infile, 2);
	ft_putstr_fd("\n", 2);
}
