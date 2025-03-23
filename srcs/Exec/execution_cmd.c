#include "../../includes/minshell.h"

/**
    STEP : 

    1/ FORK
    2/ REDIRIGE les fichiers
    3/ TRANSFORME & EXECUTE la cmd


 */


void    ft_executer(t_mshell instructions)
{
    //cehck si BI
    // redirection si necessaire (cf. redirect.c)
    forker();
    redirect(t_mshell instructions);
 
    // redirect_in ?

    // redirect_out ?

    // commandes
    execution_cmd();

}

void    forker()
{
    pid_t pid = fork();
    if (pid == 0)  // Processus enfant
    {
        // Redirection d'entrée
        if (infile != -1)
        {
            dup2(infile, STDIN_FILENO);
            close(infile);
        }
        // Redirection de sortie
        if (outfile != -1)
        {
            dup2(outfile, STDOUT_FILENO);
            close(outfile);
        }
        // Exécuter la commande
        execve(cmd_path, args_args, env);
        perror("execve"); // En cas d'échec
        exit(EXIT_FAILURE);
    }
}






void    execution_cmd()
{
    // transformation de la commande
    char *cmd_path;
    char *argv[];
    char *envp[];
    envp = getenv() ?? //char* vs char** ? ; //char *getenv(char *name)


    execve(cmd_path, cmd_args, envp)
    /*
    if (execve == -1){ // secu
        perror("Execve child1 ");
        ft_free(cmd_args);
        exit(EXIT_FAILURE);
    }
    */


}