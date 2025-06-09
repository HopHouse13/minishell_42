#include "../../includes/minishell.h"

int	ft_count_node(t_env *env_list)
{
	int	count;

	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list->next;
	}
	return (count);
}

void	ft_ignore_underscore(t_env *env_list, int *count)
{
	while (env_list)
	{
		if (!ft_strcmp(env_list->key, "_"))
		{
			env_list->ignore = true;
			(*count)--;
		}
		env_list = env_list->next;
	}
}

void	ft_init_ignore(t_env *env_list)
{
	while (env_list)
	{
		env_list->ignore = false;
		env_list = env_list->next;
	}
}


char	**ft_split_var(t_mshell *mshell, char *cmd)
{
    char    **key_value;

    if (ft_isequal(cmd))
    {
        key_value = ft_split_ml(mshell, cmd, '=');
        if (!key_value || !key_value[0])
            return NULL;
    }
    return (key_value);
}

int		ft_isequal(char *str)
{
    int	i;
    
	i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}