#include "../../includes/minishell.h"

void	ft_build_env_list(t_mshell *mshell, char **envp)
{
	t_env	*new_node;
	int		i;

	i = 0;
	while (envp[i])
	{
		new_node = ft_create_env_node(mshell);
		if (!new_node)
			return ;
		new_node->key = ft_get_env_key(envp[i]);
		if (ft_isequal(envp[i]))
				new_node->equal = true;
		new_node->value = ft_get_envp_value(envp[i]);
		i++;
	}
}

char	*ft_get_env_key(char *envp)	// recupere KEY depuis str [KEY | = value]
{
	return (ft_substr(envp, 0, ft_strlen_equal(envp)));
}

int		ft_strlen_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	return (i);
}

char	*ft_get_envp_value(char *envp) // recupere VALUE depuis str [key = | VALUE] 
{
	char	*value;
	int		i;

	if (ft_isequal(envp))
	{
		i = 0;
		while (envp[i] && envp[i] != '=')
			i++;
		if (envp[i +1])
			value = ft_substr(envp, ft_strlen_equal(envp)+1, ft_strlen(envp));
		else
			value = ft_strdup("");
		return (value);
	}
	return (NULL);
}

t_env	*ft_create_env_node(t_mshell *mshell)
{
	t_env	*new_node;
	t_env	*current_env_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		free(new_node);
		new_node = NULL;
		return (NULL);
	}
	new_node = ft_init_env_node(new_node);
	if (!mshell->env_list)
		mshell->env_list = new_node;
	else
	{
		current_env_node = mshell->env_list;
		while (current_env_node->next)
			current_env_node = current_env_node->next;
		current_env_node->next = new_node;
		new_node->prev = current_env_node;
	}
	return (new_node);
}

t_env	*ft_init_env_node(t_env *new_node)
{
	new_node->key = NULL;
	new_node->value = NULL;
	new_node->equal = false;
	new_node->ignore = false;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	ft_update_env_value(t_mshell *mshell, char *key, char *value)
{
	t_env	*env_node;

	env_node = mshell->env_list;
	while (env_node)
	{
		if (ft_strcmp(env_node->key, key) == 0)
		{
			if (value)
				env_node->value = ft_strdup_ml(mshell, value);
			else if (!value)
				env_node->value = ft_strdup_ml(mshell, "");
			return ;
		}
		env_node = env_node->next;
    }
}

t_env	*ft_check_env_key(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}


char	*ft_get_env_value(t_mshell *mshell, char *key)
{
	t_env	*env;

	env = mshell->env_list;
	while (env->next != NULL)
	{

		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int		ft_isenv_key(t_mshell *mshell, char *key)  // bool pour detecter presence '='
{
	t_env	*env;

	env = mshell->env_list;
	while (env != NULL)
	{
		if (!ft_strcmp(env->key, key))
			return (1);
		env = env->next;
	}
	return (0);
}





/*
void	ft_update_env(t_mshell *mshell, char *key)
{
	t_env	*env_list;

	env_list = mshell->env_list;
	// concernant PWD, il existe pas tant que ya pas eu de mouv.

	//OLDPWD 
	if (!ft_check_env_key(env_list, key))
	{
		//  creer OLDPWD
		// **TODO **
	}

	// nouvelle value PWD maj
	while (env_list)
	{
		if (ft_check_env_key(env_list, key))
		{
			//free
			env_list->value = getcwd(NULL, 0); //pwd 
		}
		env_list = env_list->next;
	}
	//value = ft_strdup(new_cwd);
	return ;
}

*/