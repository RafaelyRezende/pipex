#include "libpipex.h"

int main(int argc, char **argv, char **envp)
{
	t_env	this;
	pid_t	process_id;
	t_cmd	*current;

	if (argc != 5 )
	{
		ft_printf("Wrong number of arguments");
		return (-1);
	}
	if (ft_init_env(&this, argc, argv, envp))
		return (ft_cleanup_all(&this), -1);
	current = this.head_cmd;
	while (current)
	{
		ft_printf("%s\t\t%s\t\t%s\n",
						current->cmd_str,
						current->cmd_path,
						current->cmd_split[0]);
		current = current->next;
	}
	pipe(this.pipe_fd);
	this.file_fd[0] = open(this.infile, O_RDONLY);
	this.file_fd[1] = open(this.outfile, O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, 0671);
	process_id = fork();
	if (process_id == -1)
	{
		perror("fork");
		ft_cleanup_all(&this);
		exit(0);
	}
	else if (process_id == 0) // children process
	{
		if (dup2(this.file_fd[0], STDIN_FILENO) == -1)
		{
			perror("dup");
			ft_cleanup_all(&this);
			exit(EINTR);
		}
		if (dup2(this.pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
		{
			perror("dup");
			ft_cleanup_all(&this);
			exit(EINTR);
		}
		close(this.file_fd[0]);
		close(this.file_fd[1]);
		if (execve(this.head_cmd->cmd_path, &this.head_cmd->cmd_split[1], envp) == -1)
		{
			perror("exec");
			ft_cleanup_all(&this);
			exit(EIO);
		}
	}
	process_id = fork();
	if (process_id == -1)
	{
		perror("fork");
		ft_cleanup_all(&this);
		exit(0);
	}
	else if (process_id == 0) // children process
	{
		if (dup2(this.pipe_fd[READ_END], STDIN_FILENO) == -1)
		{
			perror("dup");
			ft_cleanup_all(&this);
			exit(EINTR);
		}
		if (dup2(this.file_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup");
			ft_cleanup_all(&this);
			exit(EINTR);
		}
		close(this.file_fd[0]);
		close(this.file_fd[1]);
		if (execve(this.head_cmd->cmd_path, &this.head_cmd->cmd_split[1], envp) == -1)
		{
			perror("exec");
			ft_cleanup_all(&this);
			exit(EIO);
		}
	}
	ft_cleanup_all(&this);
	return (0);
}
