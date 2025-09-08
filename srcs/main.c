#include "libpipex.h"

static int	ft_get_commands(t_cmd **head, char **av, int ac);
static void	ft_cleanup_env(t_cmd **cmd_lst);
static char	*ft_verify_command(char **s_paths, char *cmd);
static char	*ft_get_fullpath(char **envp, t_cmd *head);
static void	ft_free_all(char **split);

int main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd_lst;
	t_cmd	*current;

	if (argc != 5 )
	{
		ft_printf("Wrong number of arguments");
		return (-1);
	}
	ft_print_pid();
	cmd_lst = NULL;
	current = NULL;
	if (ft_get_commands(&cmd_lst, &argv[1], argc))
		return (ft_cleanup_env(&cmd_lst), -1);
	current = cmd_lst;
	while (current)
	{
		current->cmd_path = ft_get_fullpath(envp, current);
		ft_printf("%s\t\t%s\t\t%d\n",
						current->cmd_str,
						current->cmd_path,
						current->status);
		current = current->next;
	}
	ft_cleanup_env(&cmd_lst);
	return (0);
}

static
void	ft_free_all(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

static
void	ft_cleanup_env(t_cmd **cmd_lst)
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
		free(*cmd_lst);
		*cmd_lst = ptr_next;
	}
	*cmd_lst = NULL;
}

static
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

static
char	*ft_get_fullpath(char **envp, t_cmd *head)
{
	t_cmd	*current;
	char	*tmp;
	char	**secure_paths;

	current = head;
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
			break ;
		envp++;
	}
	secure_paths = ft_split(*envp, ':');
	tmp = ft_verify_command(secure_paths, head->cmd_str);
	ft_free_all(secure_paths);
	return (tmp);
}

static
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
