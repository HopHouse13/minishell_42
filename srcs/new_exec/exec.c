/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:44:48 by phautena          #+#    #+#             */
/*   Updated: 2025/06/11 17:05:43 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	start_exec(t_mshell *mshell);

int	exec(t_mshell *mshell)
{
	set_path(mshell);
	// init_hd(mshell);
	if (init_pipes(mshell))
		return (1);
	print_cmd(mshell);
	start_exec(mshell);
	return (0);
}

void	start_exec(t_mshell *mshell)
{
	t_cmd	*cmd;

	cmd = mshell->list_cmd;
	//single builting thing
	while (cmd)
	{
		if (cmd->no_cmd == false)
		{
			cmd->pid = fork();
			if (cmd->pid == 0)
				child_process(cmd, mshell);
			else if (cmd->pid == -1)
				fork_error(mshell);
		}
		cmd = cmd->next;
	}
	close_pipes(mshell);
	wait_for_all(mshell);
}
