#include "../../includes/minishell.h" 

int ft_env(t_mshell *mshell)
{
	t_env	*cur;
    //if (mshell->env_list == NULL)
        //ft_env_minimal(mshell); // plutot avec ft_build_env_list ??
    cur = mshell->env_list;
	while (cur)
	{
		ft_print_env_node(cur);
		cur = cur->next;
	}
	return (0);
}


void    ft_env_minimal(t_mshell *mshell)
{ 	// PWD | SHLVL | _ 
	t_env	*new_node;
	char	cwd[1024];

	new_node = ft_create_env_node(mshell);
	new_node->key = ft_get_value_key(mshell, "PWD");
	new_node->value = getcwd(cwd, sizeof(cwd));
	printf("Node PWD :\nKEY : %s\nVALUE :%s\n",new_node->key, new_node->value);

    // si env -i cad , minishell lancé avec un environnement vide, copie des variable minimale ?
    // TO DO

}


