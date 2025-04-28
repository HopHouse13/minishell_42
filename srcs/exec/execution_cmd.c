#include "../../includes/minishell.h"

/**                         EXEC MINISHELL
    STEP : 
        1/ FORK
        2/ REDIRIGE les fichiers——— (IN,OUT, PIPE)
        3/ TRANSFORME & EXECUTE la cmd
 */

/* ft_executer
    
    - check si BI 
    - - check si heredoc --> surperflu déjà dans parsing ?
    - Si << trouvé :
        lire le contenu (readline)
        créer un pipe temporaire
        écrire dedans
        rediriger stdin de la commande vers le read-end du pipe
    - check env
    
    - check pipe
    - - créer n-1 pipe
    - - redirections entrées/sorties selon pipe précédent-suivant
    - - fork 
    - - fermeture des piping

    - execution cmd
*/


void    ft_executer(t_mshell *mshell)
{
    //ft_env(mshell);
    if (mshell->list_token->token == BI)
    	printf("c'est un built in\n");/*  ft_exe_built_in(mshell); */
    else
    {
        printf("Pas un BI, c'est une commande basique : \033[33m%s\033[0m\n",mshell->list_cmd->cmd[0]);
		//ft_forker(mshell);
    }
     
    //ft_forker_test(mshell); // no pipe
    //if (BI && !(mshell->token->PIPE)) // relou, simplification avec precision dans t_cmd ?
    //{
        //ft_check_hd
            /*
                read_tempo
                pipe
                ecriture a travers pipes.
                rediriger stdin de la commande. vers le read-end. du pipe
            */
        //ft_redirect ?
        //ft_exe_built_in(mshell);
    //}

    //redirect(mshell); // dans le parent ou dans l'enfant ?
    printf("fin de l'exec.\n");
}















// _________ _________________________ ________________________ _________ __ //

/*
    FORK
    REDIRECTION
    EXECUTION 
*/

/*
void    ft_forker_test(t_mshell *mshell)
{
    //mshell->env = test_env_init("defaut"); //"defaut" ou "vide" (env -i) 

    pid_t pid;
    
    //   ----- SIMULATION INPUT
    
    mshell->list_cmd = cmd_init();
    mshell = cmd_remplissage(mshell);

    //   ------
    t_cmd *cmd_node = mshell->list_cmd->next;
    
    while(cmd_node)
    {
        pid = fork();
        if (pid == 0)
        {
            //SECURITE
            if (!cmd_node || !cmd_node->cmd || !cmd_node->cmd[0])
            {
                printf("Commande vide !\n");
                exit(EXIT_FAILURE);
            }


            //DEBUG
            printf("Commande en cours : ");
            int i = 0;
            while(cmd_node->cmd[i])
            {
                printf("\033[33m%s \033[0m", cmd_node->cmd[i]);
                i++;
            }
            printf("\n");


            //EXECUTION (manque chemin relatif)
            if(execve(cmd_node->cmd[0], cmd_node->cmd, NULL) == -1)
            {
                perror("Execve child \n");
                exit(EXIT_FAILURE);
            }
        }
        else 
            wait(NULL);
        cmd_node = cmd_node->next;
    }
} 


void    ft_forker(t_mshell *mshell)
{
    //mshell->env = test_env_init("defaut"); //"defaut" ou "vide" (env -i) 

    pid_t pid;
    
    //   ----- SIMULATION INPUT
    
    mshell->list_cmd = cmd_init();
    mshell = cmd_remplissage(mshell);

    //   ------
    t_cmd *cmd_node = mshell->list_cmd->next;
    
    while(cmd_node)
    {
        pid = fork();
        if (pid == 0)
        {
            //SECURITE
            if (!cmd_node || !cmd_node->cmd || !cmd_node->cmd[0])
            {
                printf("Commande vide !\n");
                exit(EXIT_FAILURE);
            }


            //DEBUG
            printf("Commande en cours : ");
            int i = 0;
            while(cmd_node->cmd[i])
            {
                printf("\033[33m%s \033[0m", cmd_node->cmd[i]);
                i++;
            }
            printf("\n");


            //EXECUTION (manque chemin relatif)
            if(execve(cmd_node->cmd[0], cmd_node->cmd, NULL) == -1)
            {
                perror("Execve child \n");
                exit(EXIT_FAILURE);
            }
        }
        else 
            wait(NULL);
        cmd_node = cmd_node->next;
    }
} 


void    ft_redirect(t_mshell mshell)
{
    // Redirection d'entrée
        if (infile != -1) // indicateur de redirection
        {
            dup2(infile, STDIN_FILENO); // NEED fichier & mode 
            close(infile);
        }
        // Redirection de sortie
        if (mshell->token == REDIR_OUT_Q || mshell->token == APPEND) // indicateur de redirection
        {
            dup2(outfile, STDOUT_FILENO);
            close(outfile);
        }
}*/
