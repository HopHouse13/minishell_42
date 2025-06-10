/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utilities_0.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 09:55:05 by pab               #+#    #+#             */
/*   Updated: 2025/06/10 09:57:27 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_node(t_env *env_list)
{
	int	count;

	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list->next;
	}
	return (count);
}

bool	ft_isequal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
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

char	*ft_get_key(char *var)
{
	return (ft_substr(var, 0, ft_strlen_equal(var)));
}

// recupere VALUE depuis str [key = | VALUE]
char	*ft_get_value(char *var)
{
	char	*value;
	int		i;

	if (ft_isequal(var))
	{
		i = 0;
		while (var[i] && var[i] != '=')
			i++;
		if (var[i +1])
			value = ft_substr(var, ft_strlen_equal(var) + 1, ft_strlen(var));
		else
			value = ft_strdup("");
		return (value);
	}
	return (NULL);
}
