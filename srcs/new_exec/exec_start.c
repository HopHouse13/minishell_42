/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:43:54 by phautena          #+#    #+#             */
/*   Updated: 2025/06/19 16:18:43 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	make_dup(t_cmd *cmd)
{
	dup2(cmd->fd_in, STDIN_FILENO);
	dup2(cmd->fd_out, STDOUT_FILENO);
}

void	close_pipes(t_mshell *mshell)
{
	t_cmd	*cmd;

	cmd = mshell->list_cmd;
	while (cmd)
	{
		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		cmd = cmd->next;
	}
}

void	check_cmd(t_cmd *cmd, t_mshell *mshell)
{
	struct stat	path_stat;

	if (ft_strchr(cmd->path, '/'))
	{
		if (access(cmd->path, F_OK) == -1)
		{
			ft_put_error(cmd->path, ": No such file or directory\n");
			free_mshell(mshell);
			exit(127);
		}
		else if (access(cmd->path, X_OK) == -1)
		{
			ft_put_error(cmd->path, ": Permission denied\n");
			free_mshell(mshell);
			exit(126);
		}
	}
	if (access(cmd->path, X_OK) == -1 || (!stat(cmd->path, &path_stat)
			&& S_ISDIR(path_stat.st_mode)))
	{
		ft_put_error(cmd->path, ": command not found\n");
		free_mshell(mshell);
		exit(127);
	}
}

void	wait_for_all(t_mshell *mshell)
{
	t_cmd	*temp;
	int		status;

	temp = mshell->list_cmd;
	while (temp)
	{
		if (temp->pid > -1)
		{
			waitpid(temp->pid, &status, 0);
			if (temp->next && !ft_strcmp(temp->next->cmd[0], "echo")
				&& temp->next->no_cmd == true)
				g_exit_code = 1;
			else if (WIFEXITED(status))
				g_exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_code = 128 + WTERMSIG(status);
		}
		temp = temp->next;
	}
}
