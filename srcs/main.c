/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:25:32 by pbret             #+#    #+#             */
/*   Updated: 2025/05/21 14:38:50 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_exit_code;

int	main(int ac, char **av, char **env)
{ env = NULL; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	t_mshell	*mshell;
	// t_mnode		*ml;

	ft_init_mshell(&mshell/* , env */);
	while (ac && av)
	{
		// ft_signal(1); // je sais pas encore comment gerer ca
		mshell->input = readline("minishell$ ");
		if (!mshell->input)
			break ;
		else
		{
			//ft_signal(2)
			ft_handle_input(mshell);
			if (ft_empty_line(mshell->input))
				continue ;
			if (ft_lexer(mshell))
				continue ;
			if (ft_parser(mshell))
				continue ;
			//ft_executer(mshell, env, &ml);
		}
	}
	rl_clear_history();
	ft_free_ml(mshell); // a voir
	ft_free_env(&mshell->env_list);
	free((*mshell).qts);
	free(mshell);
}
