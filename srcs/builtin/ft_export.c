#include "../../includes/minishell.h"

int ft_export(t_mshell *mshell)
{
    t_cmd   *cmd;
    cmd = mshell->list_cmd;
    
    if (!cmd->cmd[1])
		ft_print_sorted_env(mshell->env_list);
    else
        ft_add_var(mshell);
    return (1);
}

void	ft_add_var(t_mshell *mshell)
{
	t_cmd    *list_cmd;
	int i;
	
	list_cmd = mshell->list_cmd;
	i = 1;
	while (list_cmd->cmd[i])
	{
		ft_add_node_env(mshell, list_cmd->cmd[i]);
		i++;
	}
}

void    ft_add_node_env(t_mshell *mshell, char *cmd)
{
    char    **key_value;

    key_value = ft_split_var(cmd);
	if (!key_value || !key_value[0])
            return ;
	if (!ft_check_env_key(mshell->env_list, key_value))
	{
		printf(CYAN"[INFO]Creation new Env variable"RESET"\n");
		ft_create_env_node(mshell, key_value);
	}
	else
	{
		printf(CYAN"[INFO]changement value Env"RESET"\n");
		ft_change_env_value(mshell->env_list, key_value);
	}

    ft_free_tab(key_value);
}

void	ft_create_env_node(t_mshell *mshell, char **key_value)
{
	t_env	*tmp;
	t_env   *new_node;

	tmp = mshell->env_list;
	new_node = malloc(sizeof(t_env));
    if (!new_node)
        return ;
    new_node->key = ft_strdup(key_value[0]);
    if (key_value[1])
        new_node->value = ft_strdup(key_value[1]);
    else
        new_node->value = ft_strdup("");
    new_node->next = NULL;
    new_node->prev = NULL;

    if (!mshell->env_list)
        mshell->env_list = new_node;
    else
    {
        // tmp = mshell->env_list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_node;
        new_node->prev = tmp;
    } //ft_isable ??

    //ft_free_tab(key_value);
}

void	ft_change_env_value(t_env *env, char **key_value)
{
	while (env)
    {
        if (ft_strcmp(env->key, key_value[0]) == 0)
        {
            free(env->value);
            if (key_value[1])
                env->value = ft_strdup(key_value[1]);
            else
                env->value = ft_strdup("");
            ft_free_tab(key_value);
            return ;
        }
        env = env->next;
    }
}



int ft_isequal(char *str)
{
    int i;
    i = 0;

    while (str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

char **ft_split_var(char *cmd)
{
    char    **key_value;

    if (ft_isequal(cmd))
    {
        key_value = ft_split(cmd, '=');
        if (!key_value || !key_value[0])
            return NULL;
    }
    return (key_value);
}

void    ft_free_tab(char **tab)
{
    int i = 0;
    while (tab[i])
        free(tab[i++]);
    free(tab);
}

void	ft_swap_env(t_env *a, t_env *b)
{
	char *tmp_key;
	char *tmp_value;

	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;

}

void	ft_print_sorted_env(t_env *env)
{
	t_env *cur;
	t_env *tmp;

	if (!env || !env)
		return ;
	cur = env;
	while (cur->next)
	{
		tmp = cur->next;
		while (tmp)
		{
			if (ft_strcmp(cur->key, tmp->key) > 0)
				ft_swap_env(cur, tmp);
			tmp = tmp->next;
		}
		cur = cur->next;
	}
	ft_print_env_list(env);
}

// /*
//     // /!\ sensible a la casse
//     // si plusieurs args apres  ; plusieurs ajouts

//     // --> Si export est lancé sans argument 
//     //  ==> Affiche la liste env_list triée par ordre alphabétique (optionnel mais recommandé).
//     //
//     //  ft_print_list_env_sort()
    
//     // --> Si export VAR  
//     //  ==> VAR=''

//     // --> Si export VAR=value
//     //  ==> ajoute la var. si elle n’existe pas, sinon met à jour sa value
      


//     //CASES : 

//     ***
//         export VUR ou VUR=
//     ===>
//         VUR=''

//     ***
//         export VOR= eee
//     ===> 
//         VOR=''
//         eee=''

//     ***
//         export 'VIAR= eee' ou "VIAR= eee"
//     ===>
//         VIAR=' eee'

// */

//     //---------------
//     //logique 
//     // check si export + arg ? Y/N
//     // check si arg contient '=' ? Y/N
//     // entre '=' et '\0' ; '\n' ; '\t' while after = 


    //---------------