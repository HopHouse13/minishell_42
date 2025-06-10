/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:55:13 by phautena          #+#    #+#             */
/*   Updated: 2025/06/10 17:06:16 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
