/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:14:27 by pab               #+#    #+#             */
/*   Updated: 2025/06/09 00:12:07 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_sorted_env(t_env *env_list)
{
	t_env	*mini_node;
	t_env	*list;
	int		count;
	
	count = ft_count_node(env_list);
	ft_ignore_underscore(env_list, &count);
	while (count > 0)
	{
		list = env_list;
		while (list->next && list->ignore)
			list = list->next;
		mini_node = list;
		list = env_list;
		while (list)
		{
			if (!list->ignore && ft_strcmp(list->key, mini_node->key) < 0)
				mini_node = list;
			list = list->next;
		}
		mini_node->ignore = true;
		printf("export ");
		ft_print_env_node(mini_node);
		count--;
	}
	ft_init_ignore(env_list);
}

void	ft_update_env_node(t_mshell *mshell, char *str)
{
	t_env	*env_list;
	
	env_list = mshell->env_list;
	while (env_list)
	{
		if (!ft_strcmp(env_list->key, ft_get_env_key(str)))
		{
			env_list->value = ft_get_envp_value(str);
			return ;
		}
		env_list = env_list->next;
	}
	return ;
}

void	ft_print_env_node(t_env *env)
{
	if (env->equal)
	{
		printf(BLUE"%s"RESET, env->key);
		printf(WHITE"=");
		if (env->ignore)
			printf(RED"\"%s\""RESET"\n", env->value);
		else
			printf(RED"%s"RESET"\n", env->value);
	}
	else
		printf(RED"%s"RESET"\n", env->key);
}

int	ft_export(t_mshell *mshell)
{
	t_cmd   *list_cmd;
	t_env	*new_node;
	int		i;

	list_cmd = mshell->list_cmd;
	i = 1;
	if (!list_cmd->cmd[1])
		ft_print_sorted_env(mshell->env_list);
	else
	{
		while(list_cmd->cmd[i])
		{
			if (ft_found_key(mshell->env_list, ft_get_env_key(list_cmd->cmd[i])))
			{
				new_node = ft_found_key(mshell->env_list, ft_get_env_key(list_cmd->cmd[i]));
				ft_update_env_node(mshell, list_cmd->cmd[i]);
			}
			else
			{
				new_node = ft_create_env_node(mshell);
				new_node->key = ft_get_env_key(list_cmd->cmd[i]);
				if (ft_isequal(list_cmd->cmd[i]))
					new_node->equal = true;
				new_node->value = ft_get_envp_value(list_cmd->cmd[i]);
			}
			i++;
		}
	}
	return (0);
}
