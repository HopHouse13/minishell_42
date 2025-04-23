#include "../../includes/minishell.h"

t_cmd    *cmd_init(void)
{
    //creation d'une liste chainée test qui servira a envoyer les data à une autre fonction pour servir de test
    t_cmd *test;

    test = malloc(sizeof(t_cmd));
    if (!test)
        return (NULL);
    test->cmd = NULL;
    test->prev = NULL;
    test->next = NULL;
    return (test);
}
/*
t_mshell    *cmd_remplissage_test(t_mshell *mshell)
{
    // pour test cd ; adresse Scoutshell : /Users/em/Desktop/42/Projets/Rank3/Scooutshell

    char    *cmd1[] = {"/bin/ls", NULL};
    char    *cmd2[] = {"/bin/ls", "-la", NULL};
    char    *cmd3[] = {"touch", "file2.txt", NULL};
    char    *cmd4[] = {"/usr/bin/env", NULL};
    char    *cmd5[] = {"/usr/bin/touch", "file00O0.txt", NULL};



    char    **tab_global[] = {cmd1, cmd2, cmd3, cmd4, cmd5, NULL};

    t_cmd_test *current = mshell->list_cmd_test;

    int i_cmd = 0;
    while (tab_global[i_cmd])
    {
        int args_nb = 0;
        while (tab_global[i_cmd][args_nb])
            args_nb++;

        // Créer un nouveau nœud
        t_cmd_test *new_node = malloc(sizeof(t_cmd_test));
        if (!new_node)
            return (mshell);

        new_node->cmd = malloc(sizeof(char *) * (args_nb + 1)); // Un élément + NULL
        if (!new_node->cmd)
        {
            free(new_node);
            return(mshell);
        }

        // Duplication des arguments
        int j = 0;
        while (j < args_nb)
        {
            new_node->cmd[j] = ft_strdup(tab_global[i_cmd][j]);
            j++;
        }
        new_node->cmd[args_nb] = NULL;

        int m = 0;
        while (m < args_nb)    
            printf("Ajout commande : %s\n",new_node->cmd[m++]);
        
        
        new_node->redir = NULL;
        new_node->squote = false;
        new_node->dquote = false;
        new_node->hd_count = 0;
        new_node->hd = NULL;
        new_node->prev = current;
        new_node->next = NULL;
        
        current->next = new_node;
        current = new_node;
        i_cmd++;
    }
    return (mshell);
}
*/


t_mshell    *cmd_remplissage(t_mshell *mshell)
{
    // pour test cd ; adresse Scoutshell : /Users/em/Desktop/42/Projets/Rank3/Scooutshell

    char    *cmd1[] = {"/bin/ls", NULL};
    char    *cmd2[] = {"/bin/ls", "-la", NULL};
    char    *cmd3[] = {"touch", "file2.txt", NULL};
    char    *cmd4[] = {"/usr/bin/env", NULL};
    char    *cmd5[] = {"/usr/bin/touch", "file00O0.txt", NULL};



    char    **tab_global[] = {cmd1, cmd2, cmd3, cmd4, cmd5, NULL};

    t_cmd *current = mshell->list_cmd;

    int i_cmd = 0;
    while (tab_global[i_cmd])
    {
        int args_nb = 0;
        while (tab_global[i_cmd][args_nb])
            args_nb++;

        // Créer un nouveau nœud
        t_cmd *new_node = malloc(sizeof(t_cmd));
        if (!new_node)
            return (mshell);

        new_node->cmd = malloc(sizeof(char *) * (args_nb + 1)); // Un élément + NULL
        if (!new_node->cmd)
        {
            free(new_node);
            return(mshell);
        }

        // Duplication des arguments
        int j = 0;
        while (j < args_nb)
        {
            new_node->cmd[j] = ft_strdup(tab_global[i_cmd][j]);
            j++;
        }
        new_node->cmd[args_nb] = NULL;

        int m = 0;
        while (m < args_nb)    
            printf("Ajout commande : %s\n",new_node->cmd[m++]);
        
        /*
        new_node->redir = NULL;
        new_node->squote = false;
        new_node->dquote = false;
        new_node->hd_count = 0;
        new_node->hd = NULL;
        new_node->prev = current;
        new_node->next = NULL;
        */
        current->next = new_node;
        current = new_node;
        i_cmd++;
    }
    return (mshell);
}