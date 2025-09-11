#include "libpipex.h"

void	ft_free_all(char **split)
{
	int	i;

	if (!split || !*split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	ft_cleanup_lst(t_cmd **cmd_lst)
{
	t_cmd	*ptr_next;

	if (!cmd_lst)
		return ;
	while (*cmd_lst)
	{
		ptr_next = (*cmd_lst)->next;
		if ((*cmd_lst)->cmd_str)
			free((*cmd_lst)->cmd_str);
		if ((*cmd_lst)->cmd_path)
			free((*cmd_lst)->cmd_path);
		if ((*cmd_lst)->cmd_split)
			ft_free_all((*cmd_lst)->cmd_split);
		else
			free((*cmd_lst)->cmd_split);
		free(*cmd_lst);
		*cmd_lst = ptr_next;
	}
	*cmd_lst = NULL;
}

void	ft_cleanup_all(t_env *this)
{
	if (!this)
		return ;
	if (this->infile)
	{
		free(this->infile);
		this->infile = NULL;
	}
	if (this->outfile)
	{
		free(this->outfile);
		this->outfile = NULL;
	}
	ft_cleanup_lst(&this->head_cmd);
}

void	ft_cleanup_error(const char *str, t_env *this)
{
	perror(str);
	ft_cleanup_all(this);
	exit(1);
}

int	ft_error_args(void)
{
	ft_printf("Too few arguments");
	return (-1);
}
