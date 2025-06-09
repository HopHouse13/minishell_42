/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:05:55 by pab               #+#    #+#             */
/*   Updated: 2025/06/09 20:18:10 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h" 

void	ft_build_path(t_mshell *mshell)
{
	while (mshell->list_cmd)
	{	
		if (!ft_ispath(mshell->list_cmd->cmd[0]))
			ft_build_cmd_path(mshell);
		if (mshell->list_cmd->next)
			mshell->list_cmd = mshell->list_cmd->next;
		else
			break;
	}
	return ;
}

void	ft_build_cmd_path(t_mshell *mshell)
{
	char	*path_env;
	char	**path_tab;

	// printf("STRING PATH : %s\n", ft_get_env_value(mshell, "PATH"));
	path_env = ft_strdup_ml(mshell, ft_found_value_key(mshell, "PATH"));
	path_tab = ft_split_ml(mshell, path_env, ':');
	ft_path_makeur(mshell, path_tab); // Ajout '/' + 'cmd' --> Path
}

void	ft_path_makeur(t_mshell *mshell, char **path_tab)
{
	int		i;
	char	*path;
	char	**cmd;

	cmd = mshell->list_cmd->cmd;
	i = 0;
	while (path_tab[i])
	{
		path = ft_strjoin_ml(mshell, ft_strjoin_ml(mshell, path_tab[i], "/"), cmd[0]);
		if (access(path, F_OK | X_OK) == 0) //test + ajout a la liste chainee
		{
			cmd[0] = ft_strdup_ml(mshell, path);
			break;
		}
		i++;
	}
	return ;
}
