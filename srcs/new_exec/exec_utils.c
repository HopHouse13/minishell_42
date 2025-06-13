/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:55:13 by phautena          #+#    #+#             */
/*   Updated: 2025/06/13 14:35:58 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_builtin(t_mshell *mshell, t_cmd *cmd, int save, int save2)
{
	if (!ft_strcmp(cmd->path, "cd"))
		return (ft_cd(cmd->cmd, mshell));
	else if (!ft_strcmp(cmd->path, "echo"))
		return (ft_echo(cmd->cmd), 0);
	else if (!ft_strcmp(cmd->path, "pwd"))
		return (ft_pwd(), 0);
	else if (!ft_strcmp(cmd->path, "export"))
		return (ft_export_main(mshell, cmd->cmd));
	else if (!ft_strcmp(cmd->path, "env"))
		return (ft_env(mshell), 0);
	else if (!ft_strcmp(cmd->path, "exit"))
		return (ft_exit(cmd->cmd, mshell, save, save2));
	else if (!ft_strcmp(cmd->path, "unset"))
		return (ft_unset(mshell, cmd->cmd), 0);
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
