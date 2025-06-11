/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p0ulp1 <p0ulp1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:39:34 by pab               #+#    #+#             */
/*   Updated: 2025/06/11 22:56:51 by p0ulp1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_ignore_underscore(t_env *env_list, int *count)
{
	while (env_list)
	{
		if (!ft_strcmp(env_list->key, "_"))
		{
			env_list->ignore = true;
			(*count)--;
		}
		env_list = env_list->next;
	}
}

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

bool	ft_valid_key(char *c_key)
{
	int		i;
	bool	error;

	error = false;
	i = -1;
	if (!ft_isalpha(c_key[++i]))
		error = !error;
	if (!error)
	{
		while (c_key[++i])
		{
			if (!ft_isalnum(c_key[i]))
				error = !error;
		}
	}
	if (error)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(c_key, 2);
		ft_putstr_fd("' : not a valid identifier\n", 2);
		free(c_key);
		return (false);
	}
	return (true);
}

void	ft_edit_var_env(t_mshell *mshell)
{
	int		i;
	char	*c_key;
	char	*c_value;
	t_env	*new_node;

	i = 0;
	while (mshell->list_cmd->cmd[++i])
	{
		c_key = ft_get_key(mshell->list_cmd->cmd[i]);
		if (!ft_valid_key(c_key))
			continue ;
		c_value = ft_get_value(mshell->list_cmd->cmd[i]);
		if (ft_get_key_node(mshell->env_list, c_key))
			ft_up_value_var(mshell->env_list, c_key, c_value);
		else
		{
			new_node = ft_create_env_node(mshell);
			new_node->key = c_key;
			if (ft_isequal(mshell->list_cmd->cmd[i]))
				new_node->equal = true;
			new_node->value = c_value;
		}
	}
}

int	ft_export(t_mshell *mshell)
{
	if (!mshell->list_cmd->cmd[1])
		ft_print_sorted_env(mshell->env_list);
	else
		ft_edit_var_env(mshell);
	return (0);
}
