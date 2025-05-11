/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:25:32 by pbret             #+#    #+#             */
/*   Updated: 2025/05/11 20:03:24 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_exit_code;





int	main(int ac, char **av, char **env)
{
	t_mshell	*mshell;
	t_mnode		*ml;

	ft_init_mshell(&mshell, env, &ml);
	while (ac && av)
	{
		// ft_signal(1); // je sais pas encore comment gerer ca
		mshell->input = readline("minishell$ ");
		if (!mshell->input)
			break ; // sort de minishell car probleme de readline
		else
		{
			//ft_signal(2)
			if (ft_empty_line(mshell->input))
				continue ;
			if (ft_open_input(&mshell, mshell->input))
				ft_handle_close_input(&mshell, &ml);
			add_history(mshell->input);
			if (ft_lexer(mshell, &ml))
				continue ;
			if (ft_parser(mshell, &ml))
				continue ;
			ft_executer(mshell, env);
		}
	}
	rl_clear_history();
	ft_free_ml(&ml); // a voir
	ft_free_env(&mshell->env_list);
	free((*mshell).qts);
	free(mshell);
}
