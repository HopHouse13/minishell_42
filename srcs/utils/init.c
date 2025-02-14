/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:24:50 by pbret             #+#    #+#             */
/*   Updated: 2025/02/14 17:17:38 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_mshell(t_mshell *mshell, char **env)
{
	mshell->input = NULL;
	mshell->cmds_list = NULL;
	mshell->env = env;
	ft_build_paths(mshell);
}

void	ft_build_paths(t_mshell *mshell)
{
	char	*paths_line;
	int		i;
	int		j;

	i = -1;
	while (mshell->env[++i])
	{
		if (!ft_strncmp(mshell->env[i], "PATH=", 5))
		{
			j = 0;
			while (mshell->env[i][j] != '=')
				j++;
			paths_line = ft_substr(mshell->env[i], j + 1, ft_strlen(mshell->env[i]));
			if (!paths_line)
				mshell->paths == NULL;
			else
			{
				mshell->paths = ft_split(paths_line, ':');
				free (paths_line);
			}
		}
	}
}
