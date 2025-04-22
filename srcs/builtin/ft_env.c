#include "../../includes/minishell.h" 

int ft_env(t_mshell *mshell)
{
    //if (mshell->env_list == NULL)
        //ft_env_minimal(mshell->env_list);
    ft_print_env_list(mshell->env_list);
    return (1);
}

void	ft_print_env_list(t_env *env_list)
{
	while (env_list)
	{
		printf("\033[33m%s\033[0m=\033[34m%s\033[0m\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
    return ;
}

/*
void    ft_env_minimal(t_mshell *mshell)
{
    //si env -i cad , minishell lancé avec un environnement vide, copie des variable minimale ?
    ////   TO DO

}
*/

/*
char    **check_env(char **envp)
{
    char *path;

    path = getenv("PATH");

    if (!path)
    {
        //path = env_mini (pwd, shell lvl & '_')
        //mallocking en cas de env -i 
        // ** TO DO ** (voir strat avec Pab)
    }
    return (envp);
}
*/

void    ft_build_env_list(t_mshell   *mshell)
{
    //création liste chainée pour que chaque noeud soit une paire key;value
    //reprennant les variables d'environnement
    // ex : SHLVL=2   ---> t_env {char *key ; SHLVL / char *value ; 2}

    int		i = 0;
	char	**key_value;
	t_env	*new_node;
	t_env	*last = NULL;

    while (mshell->env[i])
	{
		key_value = ft_split(mshell->env[i], '=');
		if (!key_value || !key_value[0])
		{
			i++;
			continue;
		}

		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return ; // ou gérer erreur mémoire

		new_node->key = ft_strdup(key_value[0]);
        if (key_value[1])
			new_node->value = ft_strdup(key_value[1]);
		else
			new_node->value = NULL;
		//if (!(new_node->value = ft_strdup(key_value[1])))
        //    return NULL;
		new_node->prev = last;
		new_node->next = NULL;

		if (!mshell->env_list)
			mshell->env_list = new_node;
		else
			last->next = new_node;

		last = new_node;
        
		free(key_value[0]);
		if (key_value[1])
			free(key_value[1]);
		free(key_value);
        
		i++;
	}
}
