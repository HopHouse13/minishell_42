#include "../../includes/minishell.h"


void    ft_executer(t_mshell *instructions)
{
    // redirection si necessaire (cf. redirect.c)
    redirect(*instructions);
    
    // redirect_in ?

    // redirect_out ?


    // commandes
    execution_cmd();

}


void    execution_cmd()
{

    // transformation de la commande
    /*
    char *cmd_path;
    char *argv[];
    char *envp[];
    envp = getenv() ? //char* vs char** ? ; //char *getenv(char *name)


    execve(cmd_path, cmd_args, envp)
    
    */
    /*
    if (execve == -1){ // secu
        perror("Execve child1 ");
        ft_free(cmd_args);
        exit(EXIT_FAILURE);
    }
    */


}


int ft_access(char *file)
{
    if (access(file, F_OK) == 0)
        return (1);
    else
        perror("Fichier inexistant");
    return (0);
}