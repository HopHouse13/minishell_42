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
	t_cmd   *cmd;
	
	cmd = mshell->list_cmd;
	if (!cmd->cmd[1])
		ft_print_sorted_env(mshell->env_list);
	/*
	else
		ft_add_var(mshell);
	*/
	return (1);
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
		{// rajouter une secu pour key vide ?
			if (ft_strcmp(cur->key, tmp->key))
				ft_swap_env(cur, tmp);
			tmp = tmp->next;
		}
		cur = cur->next;
	}
	ft_print_env_list(env);
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