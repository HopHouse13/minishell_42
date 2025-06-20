/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:43:41 by pbret             #+#    #+#             */
/*   Updated: 2025/06/20 11:43:42 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_export(t_mshell *mshell)
{
	t_env	*env;

	env = mshell->env_list;
	while (env)
	{
		if (env->value && *env->value)
			printf("export %s=\"%s\"\n", env->key, env->value);
		else if (env->equal == true)
			printf("export %s=\"\"\n", env->key);
		else
			printf("export %s\n", env->key);
		env = env->next;
	}
}

int	ft_export_main(t_mshell *mshell, char **argv)
{
	if (!argv[1])
		print_export(mshell);
	else
		return (ft_export2(mshell, argv[1]));
	return (0);
}

int	ft_export2(t_mshell *mshell, char *argv)
{
	char	*c_key;
	char	*c_value;
	t_env	*new_node;

	c_key = ft_get_key(argv);
	if (ft_valid_key(c_key) == false)
		return (1);
	c_value = ft_get_value_2(argv);
	if (!c_value && !ft_isequal(argv))
	{
		free(c_key);
		return (0);
	}
	if (ft_get_key_node(mshell->env_list, c_key))
		ft_up_value_var(mshell->env_list, c_key, c_value);
	else
	{
		new_node = ft_create_env_node(mshell);
		new_node->key = c_key;
		if (ft_isequal(argv))
			new_node->equal = true;
		new_node->value = c_value;
	}
	return (0);
}

char	*ft_get_value_2(char *var)
{
	char	*value;
	int		i;

	if (ft_isequal(var))
	{
		i = 0;
		while (var[i] && var[i] != '=')
			i++;
		if (var[i + 1])
			value = ft_substr(var, ft_strlen_equal(var) + 1, ft_strlen(var));
		else
			value = ft_strdup("");
		return (value);
	}
	return (NULL);
}

void	ft_env(t_mshell *mshell)
{
	t_env	*env;

	env = mshell->env_list;
	while (env)
	{
		if (env->value && *env->value)
			printf("%s=%s\n", env->key, env->value);
		else if (env->equal == true)
			printf("%s=\n", env->key);
		env = env->next;
	}
}
