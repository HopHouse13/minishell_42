#include "../../includes/minishell.h"

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

void	ft_print_env_list(t_env *env_list)  //print liste chainee env[key:value]
{
	if (!env_list)
		printf("BRUHHH\n");
	while (env_list)
	{
		printf(RED"%s="RESET GREEN"%s"RESET"\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
    return ;
}