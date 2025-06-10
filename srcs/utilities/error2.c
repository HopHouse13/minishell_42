/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:09:37 by phautena          #+#    #+#             */
/*   Updated: 2025/06/10 17:18:42 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	fork_error(t_mshell *mshell)
{
	perror("fork");
	g_exit_code = 1;
	ft_exit_cleanly(mshell);
}

void	free_mshell(t_mshell *mshell)
{
	rl_clear_history();
	if (mshell->ml != NULL)
		ft_free_ml(mshell);
	if (mshell->env_list != NULL)
		ft_free_env(mshell->env_list);
	if (mshell != NULL)
		free(mshell);
}

void	ft_put_error(char *str, char *str2)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(str2, 2);
}
