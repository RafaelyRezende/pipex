#include "libpipex.h"

int	ft_ishere_doc(char **argv)
{
	if (!ft_strcmp("here_doc", argv[1]))
		return (1);
	return (0);
}

/*
void	ft_here_doc(int argc, char **argv, char **envp)
{
	t_env	this;
	t_cmd	*current;

}
*/

int	ft_init_here(t_env *this, int argc, char **argv, char **envp)
{
	t_cmd	*current;

	this->outfile = ft_strdup(argv[argc - 1]);
	if (!this->outfile)
		return (-1);
	++argv;
	if (ft_get_commands(&this->head_cmd, ++argv, argc - 1))
		return (-1);
	if (ft_get_split_commands(&this->head_cmd))
		return (-1);
	this->status = -0;
	current = this->head_cmd;
	while (current)
	{
		current->cmd_path = ft_get_fullpath(envp, current);
		current = current->next;
	}
	this->file_fd[OUTFILE_FD] = open(this->outfile, \
O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (this->file_fd[OUTFILE_FD] < 0)
		return (-1);
	return (0);
}
