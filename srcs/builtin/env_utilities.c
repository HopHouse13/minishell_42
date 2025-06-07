#include "../../includes/minishell.h"

void	ft_build_env_list(t_mshell *mshell, char **envp)
{
	t_env	*new_node;
	int		i;

	// char *key;

	i = 0;
	while (envp[i])
	{
		new_node = ft_create_env_node(mshell);
		if (!new_node)
			return ;
		new_node->key = ft_get_env_key(new_node, envp[i]);
		new_node->value = ft_get_envp_value(envp[i]);
		i++;
	}
}

char	*ft_get_env_key(t_env *node, char *envp)	
{

	if (ft_isequal(envp))
	{
		node->equal = true;
		// printf("BOOL\n");
	}
	printf(CYAN"[INFO] Input %s  ; BOOL : %d", envp, node->equal);
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

char	*ft_get_envp_value(char *envp)
{
	char	*value;
					//KEY
	if (ft_isequal(envp))
	{
		value = ft_substr(envp, ft_strlen_equal(envp)+1, ft_strlen(envp));
		if (!value)
		{
			free(value);
			value = ft_strdup(""); // /!\ Free a checker
			return (value);
		}
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

int	ft_check_env_key(t_env *env, char *key_value)
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
char	*ft_get_envp_value(char *envp)
{
	char	*value;

	value = ft_substr(envp, ft_strlen_equal(envp)+1, ft_strlen(envp));
	if (!value)
	{
		free(value);
		value = ft_strdup(""); // /!\ Free a checker
		return (value);
	}
	return (value);
}
*/

//////////////////


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