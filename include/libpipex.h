/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libpipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 08:44:30 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/09/16 08:53:01 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPIPEX_H
# define LIBPIPEX_H
# define READ_END 0
# define WRITE_END 1
# define INFILE_FD 0
# define OUTFILE_FD 1

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"

typedef struct s_cmd
{
	char			*cmd_str;
	char			*cmd_path;
	char			**cmd_split;
	pid_t			pipe_fd[2];
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_env
{
	t_cmd	*head_cmd;
	char	*infile;
	char	*outfile;
	int		*status;
	int		file_fd[2];
}	t_env;

void	ft_addfront(t_cmd **head, t_cmd *new);
void	ft_addback(t_cmd **head, t_cmd *new);
t_cmd	*ft_create_command(char *str);
int		ft_get_split_commands(t_cmd **head);
/*	CLEAN UP	*/
void	ft_cleanup_lst(t_cmd **cmd_lst);
void	ft_free_all(char **split);
void	ft_cleanup_all(t_env *this);
void	ft_cleanup_error(const char *str, t_env *this);
void	ft_err_fork(t_env *this);
int		ft_error_args(void);
/*	PARSER COMMANDS	*/
int		ft_get_commands(t_cmd **head, char **av, int ac);
char	*ft_verify_command(char **s_paths, char *cmd);
char	*ft_get_fullpath(char **envp, t_cmd *head);
int		ft_get_filename(t_env *this, int ac, char **av);
int		ft_init_env(t_env *this, int argc, char **argv, char **envp);
/*	DRIVER	*/
int		ft_process_split(t_env *this, t_cmd *current, char **envp);
int		ft_process_finisher(t_env *this, t_cmd *current, char **envp);
void	ft_process_cmd2cmd(t_env *this, t_cmd *current);
void	ft_close_all(t_env *this, t_cmd *current);
#endif
