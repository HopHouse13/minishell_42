#include "../../includes/minishell.h"



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


void	ft_print_env_list(t_env *env_list)  //print liste chainee env[key:value]
{
	if (!env_list)
		printf(RED"ENV LISTE VIDE"RESET"\n");
	while (env_list)
	{
		// KEY
		// printf("KEY= %s; BOOL = %d\n", env_list->key, env_list->equal);
		if (!env_list->equal)
		{
			printf(RED"%s"RESET"\n",env_list->key);
		}
		//KEY = && KEY=VALUE
		else
			printf(RED"%s"CYAN"="GREEN"%s"RESET"\n", env_list->key, env_list->value);
			// printf(YELLOW"%s"GREEN"%s"RESET"\n",env_list->key, env_list->value);
		env_list = env_list->next;
	}
    return ;
}

/*
void	ft_print_env_list(t_env *env_list)  //print liste chainee env[key:value]
{
	if (!env_list)
		printf(RED"ENV LISTE VIDE"RESET"\n");
	while (env_list)
	{
		if (ft_isequal(env_list->key))
		{
			printf(RED"%s="RESET, env_list->key);
			printf(GREEN"%s"RESET"\n", env_list->value);
		}
		if (!ft_isequal(env_list->key) && !env_list->value)
		{
			printf(RED"%s"RESET, env_list->key);
			printf("\tVALUE = NULL\n");
		}
		env_list = env_list->next;
	}
    return ;
}
*/