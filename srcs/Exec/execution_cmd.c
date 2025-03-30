#include "../../includes/minshell.h"

/** EXEC MINISHELL
    STEP : 
    1/ FORK
    2/ REDIRIGE les fichiers——— (IN,OUT, PIPE)
    3/ TRANSFORME & EXECUTE la cmd
 */

/* ft_executer
    - check si heredoc --> surperflu déjà dans parsing ?
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

    if (mshell->count_pipe)
        pipex(mshell); // |
    else
        forker(mshell); // no pipe

    //redirect(mshell); // dans le parent ou dans l'enfant ?
    
    // commandes
    //execution_cmd(mshell);
    printf("fin de l'exec.\n");
}

// superflu déja dans parsing ? suffit de regarder dans t_cmd
/*
bool    ft_check_hd(int count_hd)
{
    if (hd)
        return (1);

    return (0);
}
*/

bool check_BI(t_cmd *list_cmd)
{
    char    BI_list[];
    int     i;

    BI_list = {"cd", "echo", "env", "exit", "pwd", "export", "unset"};
    i = 0;

    while (i < 7)
    {
        if (ft_strmp(list_cmd->cmd[0], BI_list[i]))
            return (1);
        i++;
    }
    return (0);
}
/*
char    **check_env(char **envp)
{
    char *path;

    path = getenv("PATH");

    if (!path)
    {
        //path = env_mini (pwd, shell lvl & '_')
        //mallocking en cas de env -i 
        // ** TO DO ** (voir strat avec Pab)
    }
    return (envp);
}
*/

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
}

/*
    FORK
    REDIRECTION
    EXECUTION 
*/
void    forker(t_mshell mshell)
{
    pid_t pid;
    pid = fork();  
    if (pid == 0)  // Processus enfant
    {
        execve(mshell->list_cmd->cmd[0], mshell->list_cmd->cmd, mshell->envp)
        if (execve == -1)
        { // secu
            perror("Execve child ");
            ft_free(cmd_args);
            exit(EXIT_FAILURE);
        }
        //execution_cmd(mshell); obsolete
        /*
            // Exécuter la commande
            if (execve(mshell) == -1);
            {
                perror("execve"); // En cas d'échec
                exit(EXIT_FAILURE);
            }
        */
    }
}
/*
void    execution_cmd(t_mshell mshell)
{
    //char *cmd_path; //
    //char *argv[];   // t_cmd-> cmd
    //char *envp[];   // t_mshell-> env
    //envp = getenv() ?? //char* vs char** ? ; //char *getenv(char *name)

    
    

}
*/