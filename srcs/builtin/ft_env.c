#include "../../includes/minishell.h"

void	ft_export2(t_mshell *mshell, char *argv)
{
	char	*c_key;
	char	*c_value;
	t_env	*new_node;

	c_key = ft_get_key(argv);
	if (ft_valid_key(c_key) == false)
		return ;
	c_value = ft_get_value_2(argv);
	if (!c_value && !ft_isequal(argv))
	{
		free(c_key);
		return ;
	}
	if (ft_get_key_node(mshell->env_list, c_key))
		ft_up_value_var(mshell->env_list, c_key, c_value);
	else
	{
		new_node = ft_create_env_node(mshell);
		new_node->key = c_key;
		if (ft_isequal(argv))
			new_node->equal = true;
		new_node->value = c_value;
	}
}

char	*ft_get_value_2(char *var)
{
	char	*value;
	int		i;

	if (ft_isequal(var))
	{
		i = 0;
		while (var[i] && var[i] != '=')
			i++;
		if (var[i + 1])
			value = ft_substr(var, ft_strlen_equal(var) + 1, ft_strlen(var));
		else
			value = NULL;
		return (value);
	}
	return (NULL);
}

void	ft_env(t_mshell *mshell)
{
	t_env	*env;

	env = mshell->env_list;
	while (env)
	{
		if (env->value && *env->value)
			printf("%s=\"%s\"\n", env->key, env->value);
		else if (!env->value)
			printf("%s=\n", env->key);
		env = env->next;
	}
}

// int ft_env(t_mshell *mshell)
// {
// 	t_env	*cur;
//     //if (mshell->env_list == NULL)
//         //ft_env_minimal(mshell); // plutot avec ft_build_env_list ??
//     cur = mshell->env_list;
// 	while (cur)
// 	{
// 		ft_print_env_node(cur);
// 		cur = cur->next;
// 	}
// 	return (0);
// }


// void    ft_env_minimal(t_mshell *mshell)
// { 	// PWD | SHLVL | _
// 	t_env	*new_node;
// 	char	cwd[1024];

// 	new_node = ft_create_env_node(mshell);
// 	new_node->key = ft_found_value_key(mshell, "PWD");
// 	new_node->value = getcwd(cwd, sizeof(cwd));
// 	printf("Node PWD :\nKEY : %s\nVALUE :%s\n",new_node->key, new_node->value);

//     // si env -i cad , minishell lancé avec un environnement vide, copie des variable minimale ?
//     // TO DO

//PAUL: Si minishell est lance avec env -i, les quelques variables environnement sont quand meme copiees par ta fonction ft_build_env_list au debut de ton main.
//				--> Donc fonction inutile je pense

// }


