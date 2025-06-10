/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utilities_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:43:51 by pab               #+#    #+#             */
/*   Updated: 2025/06/10 09:59:57 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*ft_get_key_node(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

// recupere VALUE depuis une VAR existante via sa KEY
char	*ft_found_value_key(t_mshell *mshell, char *key)
{
	t_env	*env;

	env = mshell->env_list;
	while (env != NULL)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	ft_init_ignore(t_env *env_list)
{
	while (env_list)
	{
		env_list->ignore = false;
		env_list = env_list->next;
	}
}
