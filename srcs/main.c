/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:25:32 by pbret             #+#    #+#             */
/*   Updated: 2025/06/13 14:29:24 by phautena         ###   ########.fr       */
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
		ft_signals(1);
		mshell->input = readline("minishell$ ");
		if (!mshell->input)
			ft_main_err(mshell);
		else
		{
			ft_signals(2);
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
