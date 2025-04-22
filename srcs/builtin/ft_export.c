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
    
    ft_add_var(mshell);

     


    return (1);
}

void    ft_add_var(t_mshell *mshell)
{
    //fonction qui ajoute un noeud a la liste chainee (t_env *env_list)

    t_env   *new_node;
    t_env   *last;
    t_cmd    *list_cmd;

    list_cmd = mshell->list_cmd;
    
    int i;

    i = 1;
    while (list_cmd->cmd[i])
    {
        ft_add_node_env(mshell,);
        i++;
    }


}


void    ft_add_node_env(t_mshell *mshell, char *cmd)
{
    char    **key_value;
    t_env   *new_node;


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