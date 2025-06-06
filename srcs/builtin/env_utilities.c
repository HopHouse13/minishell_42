#include "../../includes/minishell.h"

void	ft_build_env_list(t_mshell *mshell, char **envp)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*new_node;

	i = 0;
	while (envp[i])
	{
		new_node = ft_create_env_node(mshell);
		if (!new_node)
			return ;
		key = ft_get_envp_key(envp[i]);
		value = ft_get_envp_value(envp[i]);
		new_node->key = key;
        new_node->value = value;
		i++;
	}
	ft_print_env_list(mshell->env_list);
}

char	*ft_get_envp_key(char *envp)	
{
	return (ft_substr(envp, 0, ft_strlen_equal(envp)));
}

int	ft_strlen_equal(char *str)
{
	int i;
	i= 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	return (i); 
}

char	*ft_get_envp_value(char *envp)
{
	char			*value;
	
	value = ft_substr(envp, ft_strlen_equal(envp) +1, ft_strlen(envp));
	if (!value)
	{
		free(value);
		value = ft_strdup("");
		return (value);
	}
	return (value);
}

t_env	*ft_create_env_node(t_mshell *mshell)
{
	t_env	*new_node;
	t_env	*current_env_list;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		free(new_node);
		new_node = NULL;
		return (NULL);
	}
	new_node->key = NULL;
	new_node->value = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	if (!mshell->env_list)
		mshell->env_list = new_node;
	else
	{
		current_env_list = mshell->env_list;
		while (current_env_list->next)
			current_env_list = current_env_list->next;
		current_env_list->next = new_node;
		new_node->prev = current_env_list;
	}
	return (new_node);
}


void	ft_update_env_value(t_mshell *mshell, char *key, char *value) // change la valeur d;un noeud
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
			//else if (ft_strcmp(env_node->value, "") == 0)
			return ;
        }
        env_node = env_node->next;
    }
}







//////////////////


char	*ft_get_env_value(t_mshell *mshell, char *key)  // value du node ?
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

int	ft_check_env_key(t_env *env, char *key_value) // key existe ?
{
	while (env)
	{
		if (ft_strcmp(env->key, key_value) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}



/*
void	ft_add_var(t_mshell *mshell)
{
	t_cmd	*list_cmd;
	int		i;

	list_cmd = mshell->list_cmd;
	i = 1;
	while (list_cmd->cmd[i])
	{
		ft_add_node_env(mshell, list_cmd->cmd[i]);
		i++;
	}
}
*/

/*
void    ft_add_node_env(t_mshell *mshell, char *cmd) // split cmd | < | {create new node env} ; {change value}
{
    char    **key_value;

    key_value = ft_split_var(mshell, cmd);
	if (!key_value || !key_value[0])
            return ;
	if (!ft_check_env_key(mshell->env_list, key_value[0]))
	{
	   printf(CYAN"[INFO]Creation new Env variable"RESET"\n");
	   ft_create_env_node(mshell, key_value);
	}
	else
	{
		printf(CYAN"[INFO]Changement value Env"RESET"\n");
		ft_change_env_value(mshell->env_list, key_value);
	}
    // ft_free_tab(key_value);
}
*/
/*
void	ft_change_env_value(t_env *env, char **key_value) // change la valeur d;un noeud
{
	while (env)
    {
        if (ft_strcmp(env->key, key_value[0]) == 0)
        {
            free(env->value);
            if (key_value[1])
                env->value = ft_strdup(key_value[1]);
            else
                env->value = ft_strdup("");
            // ft_free_tab(key_value);
            return ;
        }
        env = env->next;
    }
}
*/




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

/*
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
*/