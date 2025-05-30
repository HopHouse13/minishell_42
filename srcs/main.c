/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:25:32 by pbret             #+#    #+#             */
/*   Updated: 2025/05/27 16:44:28 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_exit_code;

int	main(int ac, char **av, char **env)
{(void)env; //ASUPPPPPPPPPPPPP!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	t_mshell	*mshell;

	ft_init_mshell(&mshell, env);
	while (ac && av)
	{
		// ft_signal(1); // je sais pas encore comment gerer ca
		ft_handle_signals();
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
			ft_executer(mshell, env);
		}
	}
	rl_clear_history();
	ft_free_ml(mshell); // a voir
	ft_free_env(mshell->env_list);
	free((*mshell).qts);
	free(mshell);
}
