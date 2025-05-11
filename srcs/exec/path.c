#include "../../includes/minishell.h" 

void	ft_build_path(t_mshell *mshell)
{
	char **cmd;
	cmd = mshell->list_cmd->cmd;

	if (ft_ispath(cmd[0]))
		return ;
	else
		ft_build_cmd_path(mshell);
	return ;
}

void	ft_build_cmd_path(t_mshell *mshell)
{
	char	*path_env;
	char	**path_tab;	

	path_env = ft_strdup(ft_get_env("PATH", mshell->env_list));
	path_tab = ft_split(path_env, ':');
	//t_print_double_tab(path_tab);
	ft_path_makeur(mshell, path_tab); // Ajout '/' + 'cmd' --> Path
	free(path_env);
	ft_free_tab(path_tab);
}

void	ft_path_makeur(t_mshell *mshell, char **path_tab)
{
	int		i;
	char	*temp;
	char	*path_join;
	char	**cmd;

	cmd = mshell->list_cmd->cmd;
	i = 0;
	while (path_tab[i])
	{
		//creation du path
		temp = ft_strjoin(path_tab[i], "/"); //what seg fault si env -i ?
		path_join = ft_strjoin(temp, cmd[0]);
		free(temp);
		if(!path_join)
		{
			perror("Path_join failed to ft_strjoin");
			return free(path_join);
		}
		if (access(path_join, F_OK | X_OK) == 0) //test + ajout a la liste chainee
		{
			free(cmd[0]);
			cmd[0] = ft_strdup(path_join);
			free(path_join);
			break;
		}
		free(path_join);
		i++;
	}
	return ;
}