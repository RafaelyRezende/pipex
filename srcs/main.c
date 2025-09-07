#include "libpipex.h"

static int	ft_get_commands(t_cmd **head, char **av);
static void	ft_cleanup_env(t_cmd **cmd_lst);

int main(int argc, char **argv)
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
	if (ft_get_commands(&cmd_lst, &argv[1]))
		return (ft_cleanup_env(&cmd_lst), -1);
	current = cmd_lst;
	while (current)
	{
		ft_printf("%s\t\t%d\n", current->cmd_str, current->status);
		current = current->next;
	}
	ft_cleanup_env(&cmd_lst);
	return (0);
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
		free(*cmd_lst);
		*cmd_lst = ptr_next;
	}
	*cmd_lst = NULL;
}

static
int	ft_get_commands(t_cmd **head, char **av)
{
	int		i;
	t_cmd	*new;

	i = 0;
	*head = NULL;
	while (av[i])
	{
		new = ft_create_command(av[i], INT_MIN);
		if (!new)
			return (-1);
		ft_addfront(head, new);
		i++;
	}
	return (0);
}
