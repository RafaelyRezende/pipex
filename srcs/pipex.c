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
	new->cmd_split = NULL;
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

int	ft_init_env(t_env *this, int argc, char **argv, char **envp)
{
	t_cmd	*current;

	if (ft_get_filename(this, argc, argv))
		return (-1);
	if (ft_get_commands(&this->head_cmd, ++argv, argc))
		return (-1);
	if (ft_get_split_commands(&this->head_cmd))
		return (-1);
	current = this->head_cmd;
	while (current)
	{
		current->cmd_path = ft_get_fullpath(envp, current);
		current = current->next;
	}
	return (0);
}
