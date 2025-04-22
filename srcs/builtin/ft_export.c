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
/*
int ft_export(t_mshell *mshell)
{
    t_cmd *cmd;
    cmd = mshell->list_cmd;
    





    ft_add_var(mshell);
   


    return (1);
}

void    ft_add_var(t_mshell *s_mshell)
{
    t_env   *new_node;
    t_env   *last;

    while (mshell->)







}

*/