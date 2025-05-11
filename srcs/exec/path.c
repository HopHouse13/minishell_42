#include "../../includes/minishell.h" 

void	ft_build_path(t_mshell *mshell, t_mnode **ml)
{
	char **cmd;
	cmd = mshell->list_cmd->cmd;

	if (ft_ispath(cmd[0]))
		return ;
	else
		ft_build_cmd_path(mshell, ml);
	return ;
}

void	ft_build_cmd_path(t_mshell *mshell, t_mnode **ml)
{
	char	*path_env;
	char	**path_tab;	

	path_env = ft_strdup_ml(ft_get_env("PATH", mshell->env_list), ml);
	path_tab = ft_split_ml(path_env, ':', ml);
	ft_path_makeur(mshell, path_tab, ml); // Ajout '/' + 'cmd' --> Path
}

void	ft_path_makeur(t_mshell *mshell, char **path_tab, t_mnode **ml)
{
	int		i;
	//char	*temp;
	char	*path;
	char	**cmd;

	cmd = mshell->list_cmd->cmd;
	i = 0;
	while (path_tab[i])
	{
		//temp = ft_strjoin_ml(path_tab[i], "/", ml); //what seg fault si env -i ?
		path = ft_strjoin_ml(ft_strjoin_ml(path_tab[i], "/", ml), cmd[0], ml);
		if (access(path, F_OK | X_OK) == 0) //test + ajout a la liste chainee
		{
			cmd[0] = ft_strdup_ml(path, ml);
			break;
		}
		i++;
	}
	return ;
}
