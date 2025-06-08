/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:14:27 by pab               #+#    #+#             */
/*   Updated: 2025/06/08 12:30:33 by pab              ###   ########.fr       */
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
			new_node = ft_create_env_node(mshell);
			if (!new_node)
				return (1);
			new_node->key = ft_get_env_key(new_node, list_cmd->cmd[i]);
			new_node->value = ft_get_envp_value(list_cmd->cmd[i]);
			i++;
		}
	}
	return (1);
}

void	ft_print_sorted_env(t_env *env_list)
{


	while (env_list->next != NULL)
	{
		if (env_list->current)
			break ;
		env_list->current = true;
		if (env_list->ignore)
		{
			env_list = env_list->next;
			env_list->next = env_list->next->next;
		}
		else
		{
			if (ft_strcmp (env_list->key, env_list->next->key) < 0)
			{
				env_list->current = false;
				env_list->next->current = true;
			}
			else if (ft_strcmp (env_list->key, env_list->next->key) > 0)
			{
				env_list->next = env_list->next->next;
			}
		}
		env_list = env_list->next;
	}

	while (env_list != NULL)
	{
		if (env_list->current)
		{
			print_env_node(env_list);
			env_list->ignore = true;
		}
		env_list = env_list->next;
	}
}

	// 2x passage de la liste 
	// 1er pour current a imprimer 				// flag : current_compare
	// 2eme pour set up le flag pour ignorer	// flag : ignore

//void	node


void	print_env_node(t_env *env)
{
	if (env->equal)
	{
		printf(BLUE BLINK"%s"RESET, env->key);
		printf(WHITE"=");
		printf(RED"%s"RESET"\n", env->value);
	}
	else
		printf(RED"%s"RESET, env->key);
}

////////

/*
void	ft_print_sorted_env(t_env *env)
{
	t_env	*cur;
	t_env	*tmp;

	if (!env || !env)
		return ;
	cur = env;
	while (cur->next)
	{
		tmp = cur->next;
		while (tmp)
		{
			if (ft_strcmp(cur->key, tmp->key))
				ft_swap_env(cur, tmp);
			tmp = tmp->next;
		}
		cur = cur->next;
	}
	ft_print_env_list(env);
}

void	ft_swap_env(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = a->key;
	a->key = b->key;
	b->key = tmp_key;
	tmp_value = a->value;
	a->value = b->value;
	b->value = tmp_value;
}
*/




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