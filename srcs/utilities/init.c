/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:38:58 by pbret             #+#    #+#             */
/*   Updated: 2025/03/29 19:39:05 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_mshell(t_mshell *mshell, char **env)
{
	mshell->input = NULL;
	mshell->list_token = NULL;
	mshell->list_cmd = NULL;
	mshell->count_pipe = 0;
	mshell->exit_status = 0;
	ft_build_env_list(mshell, env); // ! ml !!
	mshell->paths = NULL;
	//ft_build_path(mshell, ml);
}

void    ft_build_env_list(t_mshell   *mshell, char **env)
{
    int		i;
	char	**key_value;
	t_env	*new_node;
	t_env	*last = NULL;

	i = 0;
    while (env[i])
	{
		key_value = ft_split(env[i], '=');
		if (!key_value || !key_value[0])
		{
			//free ?
			i++;
		}
		new_node = malloc(sizeof(t_env)); // ! free & ml !!
		if (!new_node)
			return ;
		new_node->key = ft_strdup(key_value[0]);
        if (key_value[1])
			new_node->value = ft_strdup(key_value[1]);
		else
			new_node->value = NULL;
		new_node->prev = last;
		new_node->next = NULL;
		if (!mshell->env_list)
			mshell->env_list = new_node;
		else
			last->next = new_node;
		last = new_node;
		free(key_value[0]);
		if (key_value[1])
			free(key_value[1]);
		free(key_value);
		i++;
	}
}

/*
void	ft_build_path(t_mshell *mshell, t_mnode **ml)
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
			paths_line = ft_substr_ml(mshell->env[i], j + 1,
			ft_strlen(mshell->env[i]), ml);
			if (!paths_line)
				return ;
			else
			{
				mshell->paths = ft_split_ml(paths_line, ':', ml);
				ft_free_one_node_ml(paths_line, ml);
			}
		}
	}
}
*/
