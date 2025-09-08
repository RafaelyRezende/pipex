#ifndef PIPEX_H
# define PIPEX_H

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
	int				status;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

void	ft_print_pid(void);
void	ft_addfront(t_cmd **head, t_cmd *new);
void	ft_addback(t_cmd **head, t_cmd *new);
t_cmd	*ft_create_command(char *str);

#endif
