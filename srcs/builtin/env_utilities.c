#include "../../includes/minishell.h"

char	*ft_get_env_value(t_mshell *mshell, char *key)
{
	t_env	*env;

	env = mshell->env_list;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*ft_get_env(char *key, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_print_env_list(t_env *env_list)
{
	if (!env_list)
		printf("BRUHHH\n");
	while (env_list)
	{
		printf(BLUE"%s="RESET GREEN"%s"RESET"\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
    return ;
}
// doublon : fonction deja dans le fichier "export.c"
// int	ft_check_env_key(t_env *env, char **key_value)
// {
// 	while (env)
// 	{
// 		if (ft_strcmp(env->key, key_value[0]) == 0)
// 			return (1);
// 		env = env->next;
// 	}
// 	return (0);
// }