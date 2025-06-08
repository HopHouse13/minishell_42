#include "../../includes/minishell.h" 

int ft_env(t_mshell *mshell)
{
    //if (mshell->env_list == NULL)
        //ft_env_minimal(mshell->env_list);
    while (mshell->env_list)
	{
		ft_print_env_node(mshell->env_list);
		mshell->env_list = mshell->env_list->next;
	}
	return (0);
}





/*
void    ft_env_minimal(t_mshell *mshell)
{
    //si env -i cad , minishell lancé avec un environnement vide, copie des variable minimale ?
    ////   TO DO

}
*/

