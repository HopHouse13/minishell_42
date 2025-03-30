#include "../../includes/minshell.h"

/** EXEC MINISHELL
    STEP : 
    1/ FORK
    2/ REDIRIGE les fichiers——— (IN,OUT, PIPE)
    3/ TRANSFORME & EXECUTE la cmd
 */

/* ft_executer
    - check si heredoc
    - check si BI
    - check env
    - check pipe

    - - fork & redirection
    - - piping

    - execution cmd

*/

void    ft_executer(t_mshell mshell)
{
    ft_check_hd(mshell->list_cmd);
    ft_check_BI(mshell->list_cmd);
    ft_check_env(mshell->env);

    //fork + redirection ?
    //check si pipe
    if (mshell->count_pipe)
        pipex(mshell); // |
    else
        forker(mshell); // no pipe

    redirect(mshell); // dans le parent ou dans l'enfant ?
    
    // commandes
    execution_cmd(mshell);
    printf("fin de l'exec.\n");
}



bool check_BI(t_cmd *list_cmd)
{
    char    BI_list[];
    int     i;

    BI_list = {"cd", "echo", "env", "exit", "pwd", "export", "unset"};
    i = 0;

    while (i < 7)
    {
        if (ft_strchr(list_cmd->cmd[0], BI_list[i]))
            return (1);
        i++;
    }
    return (0);
}

char    *check_env()
{
    char *path;

    path = getenv("PATH");

    if (!path)
    {
        //path = env_mini (pwd, shell lvl & '_')
        //mallocking en cas de env -i 
        // ** TO DO ** (voir strat avec Pab)
    }
    return ();
}

void    redirigeur(t_mshell node)
{
    // Redirection d'entrée
        if (infile != -1) // indicateur de redirection
        {
            dup2(infile, STDIN_FILENO); // NEED fichier & mode 
            close(infile);
        }
        // Redirection de sortie
        if (element->token == REDIR_OUT_Q || element->token == APPEND) // indicateur de redirection
        {
            dup2(outfile, STDOUT_FILENO);
            close(outfile);
        }
}


void    forker(t_mshell element)
{
/*
    FORK
    REDIRECTION
    EXECUTION 

*/

    pid_t pid = fork();
    if (pid == 0)  // Processus enfant
    {
        // Exécuter la commande
        execve(element->paths, args_args, element->env);
        perror("execve"); // En cas d'échec
        exit(EXIT_FAILURE);
    }
}



/*
void    execution_cmd()
{
    // transformation de la commande
    char *cmd_path;
    char *argv[];
    char *envp[];
    envp = getenv() ?? //char* vs char** ? ; //char *getenv(char *name)

    execve(cmd_path, cmd_args, envp)
    
    if (execve == -1){ // secu
        perror("Execve child1 ");
        ft_free(cmd_args);
        exit(EXIT_FAILURE);
    }
    

}
*/