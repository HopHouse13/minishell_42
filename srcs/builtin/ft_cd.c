/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p0ulp1 <p0ulp1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:30:12 by pab               #+#    #+#             */
/*   Updated: 2025/06/11 23:05:15 by p0ulp1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	update_pwd(t_mshell *mshell, char *old_pwd, char *new_pwd)
{
	ft_set_var(mshell, "OLDPWD", old_pwd);
	ft_set_var(mshell, "PWD", new_pwd);
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
				printf("3\n");
			}
		}
		printf("2\n");
}

int	ft_cd(char **argv, t_mshell *mshell)
{
	int	ret;
	char	*path;
	char	*old_pwd;
	char	*new_pwd;

	if (argv[1] && argv[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (!argv[1])
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
		return (perror("minishell: cd"), 1);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (ft_mem_err(mshell), 1);
	return (update_pwd(mshell, old_pwd, new_pwd));
}

