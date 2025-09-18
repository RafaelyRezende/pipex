/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 08:45:39 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/09/18 12:16:07 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_error_args(void)
{
	ft_printf("Too few arguments");
	return (-1);
}

void	ft_err_pipe(t_env *this, int *prev_pipe)
{
	perror("pipe");
	if (*prev_pipe != -1)
		close(*prev_pipe);
	ft_close_files(this, 1);
}
