/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:25:32 by pbret             #+#    #+#             */
/*   Updated: 2025/06/12 11:36:42 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_exit_code;

int	main(int ac, char **av, char **env)
{
	t_mshell	*mshell;

	ft_init_mshell(&mshell, env);
	while (ac && av)
	{
		ft_handle_signals();
		ft_export2(mshell, "TEST=1323123");
		ft_env(mshell);
		mshell->input = readline("minishell$ ");
		if (!mshell->input)
			ft_main_err(mshell);
		else
		{
			//ft_signal(2)
			ft_handle_input(mshell);
			if (ft_empty_line(mshell->input))
				continue ;
			if (!ft_lexer(mshell))
				continue ;
			if (!ft_parser(mshell))
				continue ;
			if (exec(mshell))
				return (1);
		}
	}
	free_mshell(mshell);
}
