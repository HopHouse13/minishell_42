/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:24:50 by pbret             #+#    #+#             */
/*   Updated: 2025/02/19 13:28:22 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_mshell(t_mshell *mshell, char **env)
{
	mshell->input = NULL;
	mshell->cmds_list = NULL;
	mshell->exit_status = 0;
	mshell->env = NULL;
	ft_build_env(mshell, env);
	mshell->paths = NULL;
	ft_build_path(mshell);
}
void	ft_build_env(t_mshell *mshell, char  **env)
{	
	int	i;
	int	counter_line;
	if (!env)
		mshell->env = NULL;
	i = -1;
	counter_line = 0;
	while (env[++i])
		counter_line++;
	mshell->env = malloc((counter_line + 1) * sizeof(char *));
	i = -1;
	while (env[++i])
	{
		mshell->env[i] = ft_strdup(env[i]);
		if (mshell->env[i] == NULL)
			return ;
	}
	mshell->env[i] = NULL;
/* 	i = -1;
	while (mshell->env[++i])
		printf("%s\n", mshell->env[i]); */
}


void	ft_build_path(t_mshell *mshell)
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
				return ;
			else
			{
				mshell->paths = ft_split(paths_line, ':');
				free (paths_line);
			}
		}
	}
}
