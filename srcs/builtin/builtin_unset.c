/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:55:15 by pab               #+#    #+#             */
/*   Updated: 2025/06/09 23:19:12 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_remove_env_node(t_mshell *mshell, char *key)
{
	t_env	*prev;
	t_env	*tmp_list;
	
	if (!mshell->env_list || !key)
		return ;
	tmp_list = mshell->env_list;
	prev = NULL;
	while (tmp_list)
	{
		if (!ft_strcmp(tmp_list->key, key))
		{
			if (prev)
				prev->next = tmp_list->next;
			else
				mshell->env_list = tmp_list->next;
			free(tmp_list->key);
			free(tmp_list->value);
			free(tmp_list);
			return ;
		}
		prev = tmp_list;
		tmp_list = tmp_list->next;
	}
}

int	ft_unset(t_mshell *mshell)
{
	t_cmd	*cmd;
	int		i;

	if (!mshell || !mshell->list_cmd) // a voir
		return (0);
	cmd = mshell->list_cmd;
	i = 0;
	while (cmd->cmd[++i])
		ft_remove_env_node(mshell, cmd->cmd[i]);
	return (0);
}
