/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:25:32 by pbret             #+#    #+#             */
/*   Updated: 2025/02/17 13:51:31 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_loop_mshell(t_mshell *mshell)
{
	while (1)
	{
		//ft_signal(); // je sais pas encore comment gerer ca
		mshell->input = readline("minishell$ ");
		if (!mshell->input)
			break ;
		if (mshell->input != NULL)
			add_history(mshell->input);
		printf("input -> [%s]\n", mshell->input);
		ft_lexer(mshell, mshell->input);
	
	}
}

int	main(int ac, char **av, char **env)
{
	t_mshell	*mshell;

	(void)av; // utilisation de av pour pourvoir compiler sans erreurs.
	if (ac == 1)
	{
		mshell = malloc(sizeof(t_mshell));
		if (!mshell)
			ft_error_exit("Error main ");
		ft_init_mshell(mshell, env); // initialisation de toutes les struct
/* 		ft_print_double_tab(mshell->env);
		ft_print_double_tab(mshell->paths); */
		ft_loop_mshell(mshell);
		ft_free_manag(mshell);
		free(mshell);
		rl_clear_history();
	}
	else
	{
		errno = EINVAL; // code error du nombre d'arg inscrit dans la macro errno.
		ft_error_exit("Error main ");
	}
	return (0);
}
