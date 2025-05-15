#include "../../includes/minishell.h"

int ft_cd(t_mshell *mshell)
{
    char    *home;
	t_cmd	*cmd_node;
	
	printf(CYAN"[INFO] BI : "RESET YELLOW"cd2"RESET"\n");
	cmd_node = mshell->list_cmd;
    if (!cmd_node->cmd[1] || ft_strcmp(cmd_node->cmd[1], "~") == 0) // si 0 args "cd"
    {
        home = get_value(mshell, "HOME");
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

	//update env / pwd a faire !
    return (1);
}

