#include "../../includes/minishell.h" 

void	ft_build_path(t_cmd *list_cmd,t_env *env_list, t_mnode **ml)
{
	while (list_cmd)
	{	
		if (!ft_ispath(list_cmd->cmd[0]))
			ft_build_cmd_path(list_cmd, env_list, ml);
		if (list_cmd->next)
			list_cmd = list_cmd->next;
		else
			break;
	}
	return ;
}

void	ft_build_cmd_path(t_cmd *list_cmd,t_env *env_list, t_mnode **ml)
{
	char	*path_env;
	char	**path_tab;

	path_env = ft_strdup_ml(ft_get_env("PATH", env_list), ml);
	path_tab = ft_split_ml(path_env, ':', ml);
	ft_path_makeur(list_cmd, path_tab, ml); // Ajout '/' + 'cmd' --> Path
}

void	ft_path_makeur(t_cmd *list_cmd, char **path_tab, t_mnode **ml)
{
	int		i;
	char	*path;
	char	**cmd;

	cmd = list_cmd->cmd;
	i = 0;
	while (path_tab[i])
	{
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
