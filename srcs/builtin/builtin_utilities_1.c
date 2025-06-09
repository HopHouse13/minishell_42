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
		new_node->key = ft_get_key(envp[i]);
		if (ft_isequal(envp[i]))
				new_node->equal = true;
		new_node->value = ft_get_envp_value(envp[i]);
		i++;
	}
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
		ft_mem_err(mshell);
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

void	ft_up_value_var(t_env *env_list, char *key, char *value)
{
	if (value)
	{
		while (env_list)
		{
			if (!ft_strcmp(env_list->key, key))
			{
				if (env_list->value)
					free(env_list->value);
				env_list->value = value;
				env_list->equal = true;
			}
			env_list = env_list->next;
		}
	}
	free(key);
}

t_env	*ft_get_key_node(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*ft_get_value_key(t_mshell *mshell, char *key) // recupere VALUE depuis une VAR existante via sa KEY
{
	t_env	*env;

	env = mshell->env_list;
	while (env != NULL)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
