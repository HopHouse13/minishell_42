#include "../../includes/minishell.h"


int ft_unset(t_mshell *mshell)
{
	t_cmd	*cmd;
	int		i;

	if (!mshell || !mshell->list_cmd)
		return (0);
	cmd = mshell->list_cmd;
	i = 1;
	while (cmd->cmd[i])
	{
		ft_remove_env_node(mshell->env_list, cmd->cmd[i]);
		i++;
	}
	return (1);
}

void	ft_remove_env_node(t_env *env_list, char *key)
{
	t_env	*cur;

	if (!env_list || !env_list || !key)
		return ;
	cur = env_list;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			if (cur->prev)
				cur->prev->next = cur->next;
			else
				env_list = cur->next;
			if (cur->next)
				cur->next->prev = cur->prev;
			free(cur->key);
			free(cur->value);
			free(cur);
			return;
		}
		cur = cur->next;
	}
}
