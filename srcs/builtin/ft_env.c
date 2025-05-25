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
	t_env	*last = NULL;

 	i = 0;
    while (env[i])
 	{
 		key_value = ft_split(env[i], '=');
 		if (!key_value || !key_value[0])
 		{
 			//free ? a la fin pr
 			i++;
 		} // substr
 		new_node = malloc(sizeof(t_env)); // ! free & ml !!
 		if (!new_node)
 			return ;
 		new_node->key = ft_strdup(key_value[0]);
         if (key_value[1])
 			new_node->value = ft_strdup(key_value[1]);
 		else
 			new_node->value = NULL;
 		new_node->prev = last;
 		new_node->next = NULL;
 		if (!mshell->env_list)
 			mshell->env_list = new_node;
 		else
 			last->next = new_node;
 		last = new_node;
 		ft_free_tab(key_value);
 		i++;
 	}
}


// /*
// void    ft_env_minimal(t_mshell *mshell)
// {
//     //si env -i cad , minishell lancé avec un environnement vide, copie des variable minimale ?
//     ////   TO DO

// }
// */

