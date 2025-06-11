/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:44:48 by phautena          #+#    #+#             */
/*   Updated: 2025/06/11 17:02:32 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void	init_hd(t_mshell *mshell);

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


// void	init_hd(t_mshell *mshell)
// {
// 	t_cmd	*cmd;

// 	cmd = mshell->list_cmd;
// 	while (cmd)
// 	{
// 		if (cmd->delim_hd)
// 		{
// 			if (cmd->fd_hd > -1)
// 				close(cmd->fd_hd);
// 			cmd->fd_hd = open("./heredoc.txt", O_RDONLY);
// 			if (!cmd->fd_hd)
// 				ft_mem_err(mshell);
// 		}
// 		cmd = cmd->next;
// 	}
// }

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
