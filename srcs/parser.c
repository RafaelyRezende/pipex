/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 08:46:24 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/09/16 15:13:06 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"

int	ft_get_commands(t_cmd **head, char **av, int ac)
{
	int		i;
	t_cmd	*new;

	i = 1;
	*head = NULL;
	while (i < ac - 2)
	{
		new = ft_create_command(av[i]);
		if (!new)
			return (-1);
		ft_addback(head, new);
		i++;
	}
	return (0);
}

char	*ft_get_fullpath(char **envp, t_cmd *head)
{
	t_cmd	*current;
	char	*tmp;
	char	**secure_paths;
	int		i;

	current = head;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	secure_paths = ft_split(envp[i], ':');
	tmp = ft_verify_command(secure_paths, head->cmd_split[0]);
	ft_free_all(secure_paths);
	return (tmp);
}

char	*ft_verify_command(char **s_paths, char *cmd)
{
	char	*tmp;
	char	*tmp2;

	while (*s_paths)
	{
		tmp = ft_strjoin(*s_paths, "/");
		tmp2 = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(tmp2, X_OK))
			return (tmp2);
		free(tmp2);
		s_paths++;
	}
	return (NULL);
}

int	ft_get_split_commands(t_cmd **head)
{
	t_cmd	*current;
	char	**tmp_split;

	if (!head || !*head)
		return (-1);
	current = *head;
	while (current)
	{
		tmp_split = ft_split(current->cmd_str, ' ');
		if (!tmp_split)
			return (-1);
		current->cmd_split = tmp_split;
		current = current->next;
	}
	return (0);
}

int	ft_get_filename(t_env *this, int ac, char **av)
{
	if (av[1] && av[ac - 1])
	{
		this->infile = ft_strdup(av[1]);
		if (!this->infile)
			return (-1);
		this->outfile = ft_strdup(av[ac - 1]);
		if (!this->outfile)
			return (-1);
		return (0);
	}
	return (-1);
}
