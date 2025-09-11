#include "libpipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	this;
	t_cmd	*current;

	if (argc < 5)
		return (ft_error_args());
	if (ft_init_env(&this, argc, argv, envp))
		return (ft_cleanup_all(&this), -1);
	this.file_fd[INFILE_FD] = open(this.infile, O_RDONLY);
	this.file_fd[OUTFILE_FD] = open(this.outfile, \
O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, 0671);
	current = this.head_cmd;
	while (current)
	{
		if (!current->next)
		{
			ft_process_finisher(&this, current, envp);
			break ;
		}
		current->pipe_fd[READ_END] = ft_process_split(&this, current, envp);
		current = current->next;
	}
	while (wait(NULL) > 0)
		;
	ft_cleanup_all(&this);
	return (0);
}
