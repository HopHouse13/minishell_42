/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:25:32 by pbret             #+#    #+#             */
/*   Updated: 2025/03/05 16:25:31 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_loop_mshell(t_mshell *mshell)
{
	while (1)
	// peut etre changer la condition pour une variable stock dans la struct mshell et qui change d'etat pour sortir de minishell. (crtl+D ou exit)
	{
		// ft_signal(); // je sais pas encore comment gerer ca
		mshell->input = readline("minishell$ ");
		if (!mshell->input)
			break ;
		else
		{
			add_history(mshell->input);
			mshell->list_token = ft_lexer(mshell->input);
			if (mshell->list_token)
				ft_parser(mshell->list_token);
			// if (mshell->list_token && mshell->cmd)
			// 	ft_exec(mshell->cmd);
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
		ft_init_mshell(mshell, env); // initialisation de tes les struct
		ft_loop_mshell(mshell);      // minishell_loop
		ft_free_manag(mshell);
		ft_free_list_token(mshell->list_token);
		free(mshell);
		rl_clear_history();
	}
	else
	{
		errno = EINVAL;
		// code error du nombre d'arg inscrit dans la macro errno.
		ft_error_exit("Error main ");
	}
	return (0);
}
