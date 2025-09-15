/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:05:06 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/09/15 21:10:53 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (this.file_fd[INFILE_FD] < 0)
	{
		ft_putstr_fd("zsh: no such file or directory: ", 2);
		ft_putstr_fd(this.infile, 2);
		ft_putstr_fd("\n", 2);
	}
	this.status = 0;
	this.file_fd[OUTFILE_FD] = open(this.outfile, \
O_WRONLY | O_CREAT | O_TRUNC, 0671);
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
	waitpid(0, this.status, 0);
	ft_cleanup_all(&this);
	return (0);
}
