#include "../../includes/minishell.h" 

void    ft_exe_built_in(t_mshell *mshell, t_mnode **ml)
{
	//BI_list = {"cd", "echo", "env", "exit", "pwd", "export", "unset"};
	char *cmd;
	cmd = mshell->list_cmd->cmd[0];
	if (ft_strcmp(cmd, "cd") == 0)
	{
		printf(CYAN"[INFO] BI : "RESET YELLOW"cd"RESET"\n");
		ft_cd(mshell);
	}
	else if (ft_strcmp(cmd, "echo") == 0)
		printf("BI : \033[33mecho\033[0m\n");    
		//ft_echo();
	else if (ft_strcmp(cmd, "env") == 0)
	{
		ft_env(mshell);
		printf(CYAN"[INFO] BI : "RESET YELLOW"cd"RESET"\n");
	}
	else if (ft_strcmp(cmd, "exit") == 0)
	{
		printf("BI : "YELLOW"exit"RESET"\n");
		//ft_exit();
	}
	else if (ft_strcmp(cmd, "export") == 0)
		ft_export(mshell);
		//printf("BI   : \033[33mexport\033[0m\n");    
	else if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd(mshell, ml);
		//printf("BI : pwd\033[0m\n");    
	else if (ft_strcmp(cmd, "unset") == 0)
		printf("BI : \033[33munset\033[0m\n");    
		//ft_unset();
	else
		printf("commande differente de 'BI' : \033[31m%s\033[0m\n", cmd);
	//if (mshell)
	//ft_build_env_list(mshell);
	return ;
}