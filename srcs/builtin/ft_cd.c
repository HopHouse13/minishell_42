/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:30:12 by pab               #+#    #+#             */
/*   Updated: 2025/06/20 12:19:20 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_oldpwd(t_mshell *mshell, char *old_pwd)
{
	t_env	*env;

	env = mshell->env_list;
	while (env)
	{
		if (!ft_strcmp(env->key, "OLDPWD"))
		{
			if (env->value)
				free(env->value);
			env->value = ft_strdup(old_pwd);
			return ;
		}
		env = env->next;
	}
}

void	update_newpwd(t_mshell *mshell, char *new_pwd)
{
	t_env	*env;

	env = mshell->env_list;
	while (env)
	{
		if (!ft_strcmp(env->key, "PWD"))
		{
			if (env->value)
				free(env->value);
			env->value = ft_strdup(new_pwd);
			return ;
		}
		env = env->next;
	}
}

int	update_pwd(t_mshell *mshell, char *old_pwd, char *new_pwd)
{
	update_oldpwd(mshell, old_pwd);
	update_newpwd(mshell, new_pwd);
	free(old_pwd);
	free(new_pwd);
	return (0);
}

void	ft_set_var(t_mshell *mshell, char *key, char *value)
{
	int		i;
	t_env	*new_node;

	i = 0;
	while (mshell->list_cmd->cmd[++i])
	{
		if (ft_valid_key(key) == false)
			continue ;
		if (ft_get_key_node(mshell->env_list, value))
			ft_up_value_var(mshell->env_list, key, value);
		else
		{
			new_node = ft_create_env_node(mshell);
			new_node->key = key;
			if (ft_isequal(mshell->list_cmd->cmd[i]))
				new_node->equal = true;
			new_node->value = value;
		}
	}
}

int	ft_cd(char **argv, t_mshell *mshell)
{
	int		ret;
	char	*path;
	char	*old_pwd;
	char	*new_pwd;

	if (argv[1] && argv[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (!argv[1] || argv[1][0] == '~')
	{
		path = ft_found_value_key(mshell, "HOME");
		if (!path)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	}
	else
		path = argv[1];
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (ft_mem_err(mshell), 0);
	ret = chdir(path);
	if (ret == -1)
		return (perror("minishell: cd"), free(old_pwd), 1);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (ft_mem_err(mshell), 1);
	return (update_pwd(mshell, old_pwd, new_pwd));
}
