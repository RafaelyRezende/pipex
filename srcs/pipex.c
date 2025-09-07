#include "libpipex.h"

void	ft_print_pid(void)
{
	ft_printf("PID -> %d\n", getpid());
}

t_cmd	*ft_create_command(char *str, int status)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd_str = ft_strdup(str);
	if (!new->cmd_str)
		return (free(new), NULL);
	new->status = status;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_addfront(t_cmd **head, t_cmd *new)
{
	if (!head || !new)
		return ;
	if (*head)
	{
		new->next = *head;
		(*head)->prev = new;
		*head = new;
	}
	else
		*head = new;
}
