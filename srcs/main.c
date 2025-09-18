/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:05:06 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/09/18 12:14:48 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	this;
	t_cmd	*current;
	int		prev_pipe_read;

	if (argc < 5)
		return (ft_error_args());
	if (ft_init_env(&this, argc, argv, envp))
		return (ft_cleanup_all(&this), -1);
	prev_pipe_read = -1;
	current = this.head_cmd;
	while (current)
	{
		if (current->next != NULL && pipe(current->pipe_fd) == -1)
			ft_err_pipe(&this, &prev_pipe_read);
		current->pid = fork();
		if (current->pid == -1)
			ft_err_fork(&this, current, &prev_pipe_read);
		else if (current->pid == 0)
			ft_exec_child(&this, current, envp, &prev_pipe_read);
		ft_parent_logic(current, &prev_pipe_read);
		current = current->next;
	}
	ft_finish_pipex(&this, &prev_pipe_read);
	return (WEXITSTATUS(this.status));
}
