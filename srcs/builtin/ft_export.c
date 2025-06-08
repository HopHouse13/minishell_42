/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:14:27 by pab               #+#    #+#             */
/*   Updated: 2025/06/08 22:17:09 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(t_mshell *mshell)
{
	t_cmd   *list_cmd;
	t_env	*new_node;
	int		i;

	list_cmd = mshell->list_cmd;
	i = 1;
	if (!list_cmd->cmd[1])
		ft_print_sorted_env(mshell->env_list);
	else
	{
		while(list_cmd->cmd[i])
		{
			// if (ft_check_env_key(mshell->env_list, ft_get_env_key(list_cmd->cmd[i])))
				// new_node->value = ft_get_envp_value(list_cmd->cmd[i]);
				// ft_update_node(ft_check_env_key(mshell->env_list, ft_get_env_key(list_cmd->cmd[i])), c));
			if (ft_isenv_key(mshell, ft_get_env_key(list_cmd->cmd[i])))
			{
				new_node = ft_check_env_key(mshell->env_list, ft_get_env_key(list_cmd->cmd[i]));
				printf("Ecrasement key en cours : %s\t", new_node->key);
				ft_update_env_node(mshell, list_cmd->cmd[i]);
			}
			else
			{
				new_node = ft_create_env_node(mshell);
				if (!new_node)
				return (1);
				new_node->key = ft_get_env_key(list_cmd->cmd[i]);
				if (ft_isequal(list_cmd->cmd[i]))
					new_node->equal = true;
				printf("Creation de nouveau noeud : %s\n", new_node->key);
				new_node->value = ft_get_envp_value(list_cmd->cmd[i]);
			}
			i++;
		}
	}
	return (0);
}
void	ft_update_env_node(t_mshell *mshell, char *str)
{
	t_env	*env_list;
	// t_env	*tmp_node;
	printf("STR = %s\n",str);
	env_list = mshell->env_list;
	while (env_list)
	{
		// tmp_node = env_list;
		printf("\n\nNode en cours:\nKAY:%s\nVALUE:%s\n\n",env_list->key, env_list->value);
		if (!ft_strcmp(env_list->key, ft_get_env_key(str)))
		{
			printf("key en cours.. : %s\n", ft_get_env_key(str));
			env_list->value = ft_get_envp_value(str);
			printf("KEEEY : %s ", env_list->key);
			printf("VALUE : %s\n\n", env_list->value);
			return ;
		}
		env_list = env_list->next;
	}
	return ;
}



void	ft_print_sorted_env(t_env *env_list)
{
	t_env	*mini_node;
	t_env	*tmp_list;
	int		count;
	
	count = ft_count_node(env_list);
	ft_ignore_underscore(env_list, &count);
	while (count > 0)
	{
		tmp_list = env_list;
		while (tmp_list->next && tmp_list->ignore)
			tmp_list = tmp_list->next;
		mini_node = tmp_list;
		tmp_list = env_list;
		while (tmp_list)
		{
			if (!tmp_list->ignore && ft_strcmp(tmp_list->key, mini_node->key) < 0)
				mini_node = tmp_list;
			tmp_list = tmp_list->next;
		}
		mini_node->ignore = true;
		printf("export ");
		ft_print_env_node(mini_node);
		count--;
	}
	ft_init_ignore(env_list);
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

/*
    // /!\ sensible a la casse
    // si plusieurs args apres  ; plusieurs ajouts

    // --> Si export est lancé sans argument 
    //  ==> Affiche la liste env_list triée par ordre alphabétique (optionnel mais recommandé).
    //
    //  ft_print_list_env_sort()
    
    // --> Si export VAR  
    //  ==> VAR=''

    // --> Si export VAR=value
    //  ==> ajoute la var. si elle n’existe pas, sinon met à jour sa value

    //CASES : 

    ***
        export VUR ou VUR=
    ===>
        VUR=''

    ***
        export VOR= eee
    ===> 
        VOR=''
        eee=''

    ***
        export 'VIAR= eee' ou "VIAR= eee"
    ===>
        VIAR=' eee'

*/

    //---------------
    //logique 
    // check si export + arg ? Y/N
    // check si arg contient '=' ? Y/N
    // entre '=' et '\0' ; '\n' ; '\t' while after = 


    //---------------