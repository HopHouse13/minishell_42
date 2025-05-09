/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:25:32 by pbret             #+#    #+#             */
/*   Updated: 2025/05/09 19:13:42 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_loop_mshell(t_mshell *mshell, t_mnode **ml)
{
	while (1)
	{
		// ft_signal(1); // je sais pas encore comment gerer ca
		mshell->input = readline("minishell$ ");
		if (!mshell->input)
			break ; // sort de minishell car probleme de readline
		if (ft_empty_line(mshell->input))
			continue ;
		else
		{
			//ft_signal(2)
			add_history(mshell->input);
			ft_lexer(mshell, ml); //renvoie un list_token useless
			if (!mshell->list_token)
				continue ;
			ft_parser(mshell, mshell->list_token, ml); // renvoie un cmd_list useless
			if (!mshell->list_cmd)
				continue ;
			ft_executer(mshell);
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
		mshell = malloc(sizeof(t_mshell));
		//mshell = ft_malloc_list(sizeof(t_mshell), &ml);
		if (!mshell)
			ft_error_exit("Error main ");
		ft_init_mshell(mshell, env);
		ft_loop_mshell(mshell, &ml);
		ft_free_ml(&ml); // a voir
		rl_clear_history();
		ft_free_env(&mshell->env_list);
		free(mshell);
	}
	else
	{
		errno = EINVAL;
		// code error du nombre d'arg inscrit dans la macro errno.
		ft_error_exit("Error main ");
	}
}
