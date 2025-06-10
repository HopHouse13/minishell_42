/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:53:42 by phautena          #+#    #+#             */
/*   Updated: 2025/06/10 16:54:01 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_path(t_mshell *mshell)
{
	int		cmd_n;
	t_cmd	*cmd_temp;

	cmd_n = count_cmds(mshell);
	cmd_temp = mshell->list_cmd;
	while (cmd_n-- > 0)
	{
		if (cmd_temp->builtin == false && cmd_temp->no_cmd == false)
			set_cmd_path(mshell, cmd_temp);
		else if (cmd_temp->no_cmd == false)
		{
			cmd_temp->path = ft_strdup(cmd_temp->cmd[0]);
			if (!cmd_temp->path)
				ft_mem_err(mshell);
		}
	}
}

char	**fix_path(char **path)
{
	char	**res;
	int		len;
	int		i;

	len = 0;
	while (path[len])
		len++;
	res = malloc((len + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (path[i])
	{
		res[i] = ft_strjoin(path[i], "/");
		if (!res[i])
			return (NULL);
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	**get_path(t_mshell *mshell)
{
	char	*path;
	char	**splitted_path;
	char	**fixed;

	path = ft_found_value_key(mshell, "PATH");
	if (!path)
		return (NULL);
	splitted_path = ft_split(path, ':');
	if (!splitted_path)
		return (NULL);
	fixed = fix_path(splitted_path);
	ft_free_double_array(splitted_path);
	if (!fixed)
		return (NULL);
	return (fixed);
}

char	*get_cmd_path(char *binary, t_mshell *mshell)
{
	int		i;
	char	**path;
	char	*path_binary;

	i = 0;
	path = get_path(mshell);
	if (!path)
		return (NULL);
	while (path[i])
	{
		path_binary = ft_strjoin(path[i], binary);
		if (!path_binary)
			return (ft_free_double_array(path), NULL);
		if (!access(path_binary, F_OK))
			return (ft_free_double_array(path), path_binary);
		free(path_binary);
		i++;
	}
	ft_free_double_array(path);
	return (ft_strdup(binary));
}

void	set_cmd_path(t_mshell *mshell, t_cmd *cmd)
{
	if (cmd->cmd[0][0] != '/')
	{
		cmd->path = get_cmd_path(cmd->cmd[0], mshell);
		if (!cmd->path)
		{
			cmd->path = ft_strdup(cmd->cmd[0]);
			if (!cmd->path)
				ft_mem_err(mshell);
		}
	}
	else
	{
		cmd->path = ft_strdup(cmd->cmd[0]);
		if (!cmd->path)
			ft_mem_err(mshell);
	}
}
