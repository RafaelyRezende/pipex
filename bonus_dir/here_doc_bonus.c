/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 18:11:55 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/09/20 18:09:11 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex_bonus.h"

static
int	ft_rand_filename(t_env *this, void *stack_marker)
{
	char				*tmp;
	unsigned long		addr;
	unsigned int		res;

	tmp = NULL;
	addr = (unsigned long) stack_marker * 137;
	res = (unsigned int) addr;
	tmp = ft_itoa(res);
	this->infile = ft_strjoin("/tmp/pipex_", tmp);
	if (!this->infile)
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (0);
}

int	ft_ishere_doc(char **argv)
{
	if (!ft_strcmp("here_doc", argv[1]))
		return (1);
	return (0);
}

int	ft_init_here(t_env *this, int argc, char **argv, char **envp)
{
	t_cmd	*current;

	if (ft_create_file(this, argc, argv) < 0)
		return (-1);
	++argv;
	if (ft_get_commands(&this->head_cmd, ++argv, argc - 1))
		return (-1);
	if (ft_get_split_commands(&this->head_cmd))
		return (-1);
	this->status = 0;
	current = this->head_cmd;
	while (current)
	{
		current->cmd_path = ft_get_fullpath(envp, current);
		current = current->next;
	}
	this->file_fd[OUTFILE_FD] = open(this->outfile, \
O_WRONLY | O_CREAT | O_APPEND, 0644);
	this->file_fd[INFILE_FD] = open(this->infile, \
O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (this->file_fd[OUTFILE_FD] < 0 || this->file_fd[INFILE_FD] < 0)
		return (-1);
	return (0);
}

int	ft_create_file(t_env *this, int argc, char **argv)
{
	char	*tmp;

	if (!argv[2])
		return (-1);
	tmp = ft_strdup(argv[2]);
	this->outfile = ft_strdup(argv[argc - 1]);
	this->limiter = ft_strjoin(tmp, "\n");
	if (!this->outfile || !this->limiter)
	{
		free(tmp);
		return (-1);
	}
	if (ft_rand_filename(this, tmp) < 0)
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (0);
}

void	ft_loop(t_env *this)
{
	char	*line;

	while (1)
	{
		ft_printf("> ");
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strcmp(this->limiter, line))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, this->file_fd[INFILE_FD]);
		free(line);
	}
	close(this->file_fd[INFILE_FD]);
	this->file_fd[INFILE_FD] = open(this->infile, O_RDONLY);
	unlink(this->infile);
}
