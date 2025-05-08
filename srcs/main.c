/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:25:32 by pbret             #+#    #+#             */
/*   Updated: 2025/05/08 19:36:17 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_loop_mshell(t_mshell *mshell, t_mnode **ml)
{
	while (1)
	// peut etre changer la condition pour une variable stock dans la struct mshell et qui change d'etat pour sortir de minishell. (crtl+D ou exit)
	{
		// ft_signal(1); // je sais pas encore comment gerer ca
		mshell->input = readline("minishell$ ");
		if (!mshell->input)
			break ;
		else
		{
			//ft_signal(2)
			add_history(mshell->input);
			mshell->list_token = ft_lexer(mshell->input, ml);
			ft_print_list_token(mshell->list_token); //ASUPP
			if (mshell->list_token)
			{
				mshell->list_cmd = ft_parser(mshell, mshell->list_token, ml);
				ft_print_list_cmd(mshell); // ASUPP
				if (mshell->list_cmd)
					ft_executer(mshell);
			}
		}
	}
}
// truc a tester : avoir une $VAR dans une $VAR faut-il expand la 2eme? (endehors du heredoc)
int	main(int ac, char **av, char **env)
{
	
	t_mshell	*mshell;
	t_mnode		*ml;

	ml = NULL;
	if (av && ac == 1)
	{
		mshell = ft_malloc_list(sizeof(t_mshell), &ml);
		if (!mshell)
			ft_error_exit("Error main ");
		ft_init_mshell(mshell, env/*, &ml*/); // initialisation de tes les struct
		ft_loop_mshell(mshell, &ml);      // minishell_loop
		ft_free_ml(&ml);
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