#include "../../includes/minshell.h"


void    ft_executer(t_mshell instructions)
{

    // redirection si necessaire (cf. redirect.c)
    redirect(t_mshell instructions);
    forker();
    // redirect_in ?

    // redirect_out ?

    // commandes
    execution_cmd();





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