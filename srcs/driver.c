#include "libpipex.h"

int	ft_process_split(t_env *this, t_cmd *current, char **envp)
{
	int	process_id;

	pipe(current->pipe_fd);
	process_id = fork();
	if (process_id == -1)
	{
		perror("fork");
		ft_cleanup_all(this);
		exit(0);
	}
	else if (process_id == 0)
	{
		if (dup2(this->file_fd[INFILE_FD], STDIN_FILENO) == -1)
			ft_cleanup_error("dup", this);
		if (dup2(current->pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
			ft_cleanup_error("dup", this);
		close(this->file_fd[INFILE_FD]);
		close(this->file_fd[OUTFILE_FD]);
		if (execve(current->cmd_path, current->cmd_split, envp) == -1)
			ft_cleanup_error("exec", this);
	}
	close(current->pipe_fd[WRITE_END]);
	return (current->pipe_fd[READ_END]);
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
		close(this->file_fd[INFILE_FD]);
		close(this->file_fd[OUTFILE_FD]);
		close(current->prev->pipe_fd[READ_END]);
		if (execve(current->cmd_path, current->cmd_split, envp) == -1)
			ft_cleanup_error("exec", this);
	}
	close(current->pipe_fd[READ_END]);
	return (0);
}
