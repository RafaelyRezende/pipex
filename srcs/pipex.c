#include "libpipex.h"

t_cmd	*ft_create_command(char *str)
{
	t_cmd	*new;

	if (!*str)
		return (NULL);
	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd_str = ft_strdup(str);
	if (!new->cmd_str)
		return (free(new), NULL);
	new->cmd_path = NULL;
	new->cmd_split= NULL;
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

void	ft_addback(t_cmd **head, t_cmd *new)
{
	t_cmd	*current;

	if (!head || !new)
		return ;
	if (*head)
	{
		current = *head;
		while (current && current->next)
			current = current->next;
		current->next = new;
		new->prev = current;
	}
	else
		*head = new;
}
