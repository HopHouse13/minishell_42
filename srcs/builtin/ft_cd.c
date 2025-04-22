#include "../../includes/minishell.h"
/*
int ft_cd(t_mshell *mshell)
{
    char    *home;
    if (!cmd_node->cmd[1]) // si 0 args "cd"
    {
        home = getenv("HOME");
        if (!home || chdir(home) == -1)
        {
            perror("cd: HOME absent\n");
            return (0);
        }
    }
    else 
    {
        if (chdir(cmd_node->cmd[1]) == -1)
        {
            perror("cd");
            return (0);
        }
    }
    return (1);
}
*/