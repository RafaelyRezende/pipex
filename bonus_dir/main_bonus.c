/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:05:06 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/09/20 17:36:16 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex_bonus.h"

static int	ft_mandatory(t_env *this, char **envp);

int	main(int argc, char **argv, char **envp)
{
	t_env	this;

	if (argc < 5)
		return (ft_error_args());
	if (ft_ishere_doc(argv))
	{
		if (ft_init_here(&this, argc, argv, envp) < 0)
			return (ft_cleanup_all(&this), -1);
		ft_loop(&this);
	}
	else
	{
		if (ft_init_env(&this, argc, argv, envp))
			return (ft_cleanup_all(&this), -1);
	}
	ft_mandatory(&this, envp);
}

static
int	ft_mandatory(t_env *this, char **envp)
{
	t_cmd	*current;
	int		prev_pipe_read;

	prev_pipe_read = -1;
	current = this->head_cmd;
	while (current)
	{
		if (current->next != NULL && pipe(current->pipe_fd) == -1)
			ft_err_pipe(this, &prev_pipe_read);
		current->pid = fork();
		if (current->pid == -1)
			ft_err_fork(this, current, &prev_pipe_read);
		else if (current->pid == 0)
			ft_exec_child(this, current, envp, &prev_pipe_read);
		ft_parent_logic(current, &prev_pipe_read);
		current = current->next;
	}
	ft_finish_pipex(this, &prev_pipe_read);
	return (WEXITSTATUS(this->status));
}
