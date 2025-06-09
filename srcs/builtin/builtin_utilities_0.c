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

bool ft_isequal(char *str)
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

void	ft_print_env_node(t_env *env)
{
	if (env->equal)
	{
		printf(BLUE"%s"RESET, env->key);
		printf(WHITE"=");
		if (env->ignore)
			printf(RED"\"%s\""RESET"\n", env->value);
		else
			printf(RED"%s"RESET"\n", env->value);
	}
	else
		printf(RED"%s"RESET"\n", env->key);
}

char	*ft_get_key(char *var)
{
	return (ft_substr(var, 0, ft_strlen_equal(var)));
}

char	*ft_get_value(char *var)
{
	if (ft_isequal(var))
		return (ft_substr(var, ft_strlen_equal(var) +1, ft_strlen(var)));
	else
		return (NULL);
}
