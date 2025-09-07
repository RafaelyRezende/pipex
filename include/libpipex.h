#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <errno.h>
# include "libft.h"

typedef struct s_cmd
{
	char			*cmd_str;
	int				status;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

void	ft_print_pid(void);
void	ft_addfront(t_cmd **head, t_cmd *next);
t_cmd	*ft_create_command(char *str, int status);

#endif
