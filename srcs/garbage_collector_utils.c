/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 08:46:01 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/09/18 12:16:07 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"

void	ft_err_fork(t_env *this, t_cmd *current, int *prev_pipe)
{
	perror("fork");
	if (!current->next)
		ft_close_pipes(current);
	if (*prev_pipe != -1)
		close(*prev_pipe);
	ft_close_files(this, 1);
}

void	ft_err_dir(t_env *this)
{
	ft_putstr_fd("zsh: no such file or directory: ", 2);
	ft_putstr_fd(this->infile, 2);
	ft_putstr_fd("\n", 2);
}
