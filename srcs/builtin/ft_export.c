#include "../../includes/minishell.h"

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

int ft_export(t_mshell *mshell)
{
    //t_cmd   *cmd;
    //cmd = mshell->list_cmd;
    
    //if (!cmd[1])
    //  print_sort(mshell);
    //else
        ft_add_var(mshell);

    return (1);
}

void    ft_add_var(t_mshell *mshell)
{
    //fonction qui ajoute un noeud a la liste chainee (t_env *env_list)

    t_cmd    *list_cmd;

    list_cmd = mshell->list_cmd;
    
    int i;

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
    t_env   *tmp;
    t_env   *new_node;

    
    key_value = ft_split_var(cmd);
    /*
    if (ft_isequal(cmd))
    {
        key_value = ft_split(cmd, '=');
        if (!key_value || !key_value[0])
            return ;
    }
    */
    // Chercher si la variable existe déjà
    tmp = mshell->env_list;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, key_value[0]) == 0)
        {
            free(tmp->value);
            /*if (key_value[1])
                tmp->value = ft_strdup(key_value[1]);
            else
                tmp->value = ft_strdup("");*/
            if (key_value[1])
                tmp->value = ft_strdup(key_value[1]);
            else
                tmp->value = ft_strdup("");
            ft_free_tab(key_value);
            return ;
        }
        tmp = tmp->next;
    } // ft_isable


    ////////////////
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

    // Ajouter à la fin de la liste env_list
    if (!mshell->env_list)
        mshell->env_list = new_node;
    else
    {
        tmp = mshell->env_list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_node;
        new_node->prev = tmp;
    } //ft_isable ??

    ft_free_tab(key_value);

    if (ft_isequal(cmd))
        key_value = ft_split(cmd, '=');
    
    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return ;
    new_node->key = ft_strdup(key_value[0]);


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

