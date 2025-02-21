/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:25:32 by pbret             #+#    #+#             */
/*   Updated: 2025/02/21 14:28:04 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_loop_mshell(t_mshell *mshell)
{
	while (1) // peut etre changer la condition pour une variable stocke dans la struct mshell et qui change d'etat pour sortir de minishell. (crtl+D ou exit)
	{
		//ft_signal(); // je sais pas encore comment gerer ca
		mshell->input = readline("minishell$ ");
		if (!mshell->input)
			break ;
		else
		{
			add_history(mshell->input);
			ft_parser(mshell, mshell->input);
			// ft_lexer(mshell, mshell->input);
			// ft_exec();
		}
	
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
		ft_init_mshell(mshell, env); // initialisation de tOUT_Qes les struct
		ft_loop_mshell(mshell); // minishell_loop
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
