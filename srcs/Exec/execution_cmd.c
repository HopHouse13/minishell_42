#include "minshell.h"


void    ft_executer(t_mshell instructions)
{

    // redirection si necessaire (cf. redirect.c)
    redirect(t_mshell instructions)
    
    // redirect_in ?

    // redirect_out ?


    // commandes
    execution_cmd()





}


void    execution_cmd(char *cmd, char **cmd_args)
{
    // transformation de la commande
    char *cmd_path;
    char *argv[];
    char *envp[];
    
    //get_bin_env_path() ??
    bin_env_path = getenv() ?? //char* vs char** ? ; //char *getenv(char *name)



    execve(cmd_path, cmd_args, bin_env_path)
    /*
    if (execve == -1){ // secu
        perror("Execve child1 ");
        ft_free(cmd_args);
        exit(EXIT_FAILURE);
    }
    */


}


//
char    **get_bin_env_path(char *path)
{


}