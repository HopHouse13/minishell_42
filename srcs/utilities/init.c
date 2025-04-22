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
	//mshell->env = NULL;
	//ft_build_env(mshell, env, ml); /**/
	ft_build_env_list(mshell, env); // version def avec env
	//ft_print_env_list(mshell->env_list);
	mshell->paths = NULL;
	//ft_build_path(mshell, ml);
}


void    ft_build_env_list(t_mshell   *mshell, char **env)
{
    //création liste chainée pour que chaque noeud soit une paire key;value
    //reprennant les variables d'environnement
    // ex : SHLVL=2   ---> t_env {char *key ; SHLVL / char *value ; 2}

    int		i = 0;
	char	**key_value;
	t_env	*new_node;
	t_env	*last = NULL;

    while (env[i])
	{
		key_value = ft_split(env[i], '=');

		if (!key_value || !key_value[0])
		{
			//free ?
			i++;
			continue;
		}

		new_node = malloc(sizeof(t_env)); // /!! free & ml !!
		if (!new_node)
			return ;

		new_node->key = ft_strdup(key_value[0]);
        if (key_value[1])
			new_node->value = ft_strdup(key_value[1]);
		else
			new_node->value = NULL;
		//if (!(new_node->value = ft_strdup(key_value[1])))
        //    return NULL;
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
void	ft_build_env(t_mshell *mshell, char  **env, t_mnode **ml)
{
	int	i;
	int	counter_line;
	if (!env)
		mshell->env = NULL;
	i = -1;
	counter_line = 0;
	while (env[++i])
		counter_line++;
	mshell->env = ft_malloc_list((counter_line + 1) * sizeof(char *), ml);
	i = -1;
	while (env[++i])
	{
		mshell->env[i] = ft_strdup_ml(env[i], ml);
		if (mshell->env[i] == NULL)
			return ;
	}
	mshell->env[i] = NULL;
 	i = -1;
	while (mshell->env[++i])
		printf("%s\n", mshell->env[i]); 
}
*/
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