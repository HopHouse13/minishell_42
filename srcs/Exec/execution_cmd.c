#include "minshell.h"


void    ft_executer(t_mshell instructions)
{

    // redirection si necessaire (cf. redirect.c)
    redirect(src,dest)

    // commandes
    execution_cmd()





}



void    execution_cmd()
{
    // transformation de la commande
    execve(cmd_path, cmd_args, envp)
    /*
    if (execve == -1){ // secu
        perror("Execve child1 ");
        ft_free(cmd_args);
        exit(EXIT_FAILURE);
    }
    */


}