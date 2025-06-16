/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:44:48 by phautena          #+#    #+#             */
/*   Updated: 2025/06/16 17:39:27 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	start_exec(t_mshell *mshell);

int	exec(t_mshell *mshell)
{
	set_path(mshell);
	if (init_pipes(mshell))
		return (1);
	// print_cmd(mshell);
	start_exec(mshell);
	free_paul_stuff(mshell);
	return (0);
}

void	start_exec(t_mshell *mshell)
{
	t_cmd	*cmd;

	cmd = mshell->list_cmd;
	if (single_builtin(mshell, cmd))
		return ;
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

void	child_process(t_cmd *cmd, t_mshell *mshell)
{
	int	builtin_exit;

	if (cmd->builtin == true)
	{
		make_dup(cmd);
		close_pipes(mshell);
		builtin_exit = exec_builtin(mshell, cmd, 0, 0);
		exit(builtin_exit);
	}
	else
	{
		check_cmd(cmd, mshell);
		make_dup(cmd);
		close_pipes(mshell);
		execve(cmd->path, cmd->cmd, mshell->envp);
	}
}
