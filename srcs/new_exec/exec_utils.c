/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p0ulp1 <p0ulp1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:55:13 by phautena          #+#    #+#             */
/*   Updated: 2025/06/11 22:45:39 by p0ulp1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_builtin(t_mshell *mshell, t_cmd *cmd, int save, int save2)
{
	if (!ft_strcmp(cmd->path, "cd"))
		return (ft_cd(cmd->cmd, mshell));
	(void)save;
	(void)save2;
	return (1);
}

int	single_builtin(t_mshell *mshell, t_cmd *cmd)
{
	int	save;
	int	save2;

	if (cmd->builtin == true && !cmd->prev && !cmd->next && !cmd->no_cmd)
	{
		save = dup(STDOUT_FILENO);
		save2 = dup(STDIN_FILENO);
		if (cmd->fd_out > -1)
			dup2(cmd->fd_out, STDOUT_FILENO);
		if (cmd->fd_in > -1)
			dup2(cmd->fd_in, STDIN_FILENO);
		g_exit_code = exec_builtin(mshell, cmd, save, save2);
		dup2(save, STDOUT_FILENO);
		dup2(save2, STDIN_FILENO);
		close(save);
		close(save2);
		return (1);
	}
	return (0);
}

int	count_cmds(t_mshell *mshell)
{
	t_cmd	*tmp;
	int		res;

	tmp = mshell->list_cmd;
	res = 0;
	while (tmp)
	{
		res++;
		tmp = tmp->next;
	}
	return (res);
}

int	init_pipes(t_mshell *mshell)
{
	t_cmd	*cmd;
	int		pipefd[2];

	cmd = mshell->list_cmd;
	if (cmd->fd_in == -1)
		cmd->fd_in = STDIN_FILENO;
	while (cmd)
	{
		if (cmd->next && cmd->fd_out == -1 && cmd->next->fd_in == -1)
		{
			if (pipe(pipefd) == -1)
				return (1);
			cmd->fd_out = pipefd[1];
			cmd->next->fd_in = pipefd[0];
		}
		if (!cmd->next && cmd->fd_out == -1)
			cmd->fd_out = STDOUT_FILENO;
		cmd = cmd->next;
	}
	return (0);
}
