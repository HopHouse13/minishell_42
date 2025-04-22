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
	if (!env_list)
	{
		printf("BRUHHH\n");
	}
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
