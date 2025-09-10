#ifndef PIPEX_H
# define PIPEX_H
# define READ_END 0
# define WRITE_END 1

# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"

typedef struct s_cmd
{
	char			*cmd_str;
	char			*cmd_path;
	char			**cmd_split;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_env
{
	t_cmd	*head_cmd;
	char	*infile;
	char	*outfile;
	pid_t	pipe_fd[2];
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
/*	PARSER COMMANDS	*/
int		ft_get_commands(t_cmd **head, char **av, int ac);
char	*ft_verify_command(char **s_paths, char *cmd);
char	*ft_get_fullpath(char **envp, t_cmd *head);
int		ft_get_filename(t_env *this, int ac, char **av);
int		ft_init_env(t_env *this, int argc, char **argv, char **envp);
#endif
