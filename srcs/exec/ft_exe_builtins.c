// #include "../../includes/minishell.h" 

//BI_list = {"cd", "echo", "env", "exit", "pwd", "export", "unset"};
void	ft_exe_built_in(t_mshell *mshell, t_mnode **ml)
{
	char	*cmd;
	cmd = mshell->list_cmd->cmd[0];
	if (ft_strcmp(cmd, "cd") == 0)
	{
		printf(CYAN"[INFO] BI : "RESET YELLOW"cd"RESET"\n");
		ft_cd(mshell);
	}
	else if (ft_strcmp(cmd, "echo") == 0)
	{
		printf(CYAN"[INFO] BI : "RESET YELLOW"cd"RESET"\n");
		//ft_echo();
	}    
	else if (ft_strcmp(cmd, "env") == 0)
	{
		ft_env(mshell);
		printf(CYAN"[INFO] BI : "RESET YELLOW"env"RESET"\n");
	}
	else if (ft_strcmp(cmd, "exit") == 0)
	{
		printf("BI : "YELLOW"exit"RESET"\n");
		ft_exit(mshell->list_cmd);
	}
	else if (ft_strcmp(cmd, "export") == 0)
	{
		printf(CYAN"[INFO] BI : "RESET YELLOW"export"RESET"\n");
		ft_export(mshell);
	}    
	else if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd(mshell, ml);    
	else if (ft_strcmp(cmd, "unset") == 0)
	{
		printf(CYAN"[INFO] BI : "RESET YELLOW"unset"RESET"\n");
		ft_unset(mshell);
	}
	else
		printf("commande differente de 'BI' : \033[31m%s\033[0m\n", cmd);
	return ;
}