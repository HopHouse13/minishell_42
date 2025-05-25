#include "../../includes/minishell.h" 

void	ft_build_path(t_mshell *mshell)
{

	t_cmd	*list_cmd;
	// t_env	*env_list;
	
	list_cmd = mshell->list_cmd;
	//env_list = mshell->env_list;
	while (list_cmd)
	{	
		if (!ft_ispath(list_cmd->cmd[0]))
			ft_build_cmd_path(mshell);
		if (list_cmd->next)
			list_cmd = list_cmd->next;
		else
			break;
	}
	return ;
}

void	ft_build_cmd_path(t_mshell *mshell)
{
	char	*path_env;
	char	**path_tab;
	// t_cmd	*list_cmd;
	//t_env	*env_list;

	// list_cmd = mshell->list_cmd;
	//env_list = mshell->env_list;
	path_env = ft_strdup_ml(mshell, ft_get_env_value(mshell, "PATH"));
	path_tab = ft_split_ml(mshell, path_env, ':');
	ft_path_makeur(mshell, path_tab); // Ajout '/' + 'cmd' --> Path
}

void	ft_path_makeur(t_mshell *mshell, char **path_tab)
{
	int		i;
	char	*path;
	char	**cmd;
	
	cmd = mshell->list_cmd->cmd;
	i = 0;
	while (path_tab[i])
	{
		path = ft_strjoin_ml(mshell, cmd[0], ft_strjoin_ml(mshell, path_tab[i], "/"));
		if (access(path, F_OK | X_OK) == 0) //test + ajout a la liste chainee
		{
			cmd[0] = ft_strdup_ml(mshell, path);
			break;
		}
		i++;
	}
	return ;
}