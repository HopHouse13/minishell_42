/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:14:27 by pab               #+#    #+#             */
/*   Updated: 2025/05/27 15:14:28 by pab              ###   ########.fr       */
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
		// ft_export_value(mshell);
		//ft_add_var(mshell);
	return (1);
}

/*
void	ft_export_var(t_mshell *mshell)
{
	t_cmd	*list_cmd;
	t_env	*new_node;
	int		i;

	list_cmd = mshell->list_cmd;
	i = 1;
	while (list_cmd->cmd[i])
	{
		new_node = ft_create_env_node(mshell);
		if (!new_node)
		return ;
		new_node->key = ft_get_envp_key(list_cmd->cmd[i]);
		new_node->value = ft_get_envp_value(list_cmd->cmd[i]);
		i++;
	}
}
*/

// int	print_export_key(char *str)
// {
// 	// int	i;
// 	// i = 0;
// 	if (ft_isequal(str))
// 		printf("%s=", str);
// 	else
// }



////////

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


// 2x passage de la liste 
// 1er pour current a imprimer 				// flag : current_compare
// 2eme pour set up le flag pour ignorer	// flag : ignore



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