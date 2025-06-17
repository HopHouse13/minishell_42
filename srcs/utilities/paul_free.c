/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paul_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:00:36 by phautena          #+#    #+#             */
/*   Updated: 2025/06/17 15:09:50 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_after_exec(t_mshell *mshell)
{
	free_paul_stuff(mshell);
	if (mshell->ml)
		ft_free_ml(mshell);
}

void	free_paul_stuff(t_mshell *mshell)
{
	t_cmd	*cmd;

	cmd = mshell->list_cmd;
	while (cmd)
	{
		if (cmd->path)
		{
			free(cmd->path);
			cmd->path = NULL;
		}
		cmd = cmd->next;
	}
}

void	ft_exit_cleanly2(t_mshell *mshell)
{
	rl_clear_history();
	free_paul_stuff(mshell);
	if (mshell->ml != NULL)
		ft_free_ml(mshell);
	if (mshell->env_list != NULL)
		ft_free_env(mshell->env_list);
	if (mshell != NULL)
		free(mshell);
	exit(g_exit_code);
}
