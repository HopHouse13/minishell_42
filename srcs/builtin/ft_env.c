#include "../../includes/minishell.h" 

int ft_env(t_mshell *mshell)
{
    //if (mshell->env_list == NULL)
        //ft_env_minimal(mshell->env_list);
    ft_print_env_list(mshell->env_list);
    return (1);
}


void    ft_build_env_list(t_mshell *mshell, char **env)
{
    int		i;
	char	**key_value;
	t_env	*new_node;
	t_env	*last;

	last = NULL;
	i = 0;
    while (env[i])
	{
		key_value = ft_split_ml(mshell, env[i], '='); // substr -> possibilite de '=' dans la value de la variable d'env
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return ;
		new_node->key = ft_strdup_ml(mshell, key_value[0]);
        if (key_value[1])
			new_node->value = ft_strdup_ml(mshell, key_value[1]);
		else
			new_node->value = NULL;
		new_node->prev = last;
		new_node->next = NULL;
		if (!mshell->env_list)
			mshell->env_list = new_node;
		else
			last->next = new_node;
		last = new_node;
		i++;
	}
}


/*
void    ft_build_env_list(t_mshell *mshell, char **env)
{
    int		i;
	char	**key_value;
	t_env	*new_node;
	t_env	*last;


	// char *key;
	// char *value;

	last = NULL;
	i = 0;
    while (env[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return ; // ft_mem_err(mshell)
		key_value = ft_split_ml(mshell, env[i], '='); // substr -> possibilite de '=' dans la value de la variable d'env
		
		//key = ft_substr_ml(mshell, env[i], 0, len);
		//key = ft_substr_equal(mshell, &env[i]);
		//value = ft_substr_equal(mshell, &env[i]);
		
		//secu

		//create new node + fill with KEY
		new_node->key = ft_strdup_ml(mshell, key_value[0]);
		//new_node->key = key;
		//rajouter VALUE (dans node en cours avec passage par reference ?)
        if (key_value[1])
			new_node->value = ft_strdup_ml(mshell, key_value[1]);
			//new_node->value = value;
		else
			new_node->value = NULL;
		
		////////////
		new_node->prev = last;
		new_node->next = NULL;
		if (!mshell->env_list)
			mshell->env_list = new_node;
		else
			last->next = new_node;
		last = new_node;
		// ft_free_tab(key_value);
		i++;
	}
}
*/

/*
char	*ft_substr_equal(t_mshell *mshell, char *str)
{
	char	*substr;
	int		i;
	int		start;
	
	i = 0;

	start = ft_strchr(str, '=');

	while (str[i] != '\0' || str[i] == '=')
		i++;
	
	substr = ft_substr_ml(mshell, str, start, i);
	return (substr);
}
*/
/*
void    ft_env_minimal(t_mshell *mshell)
{
    //si env -i cad , minishell lancé avec un environnement vide, copie des variable minimale ?
    ////   TO DO

}
*/

