/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:29:58 by phautena          #+#    #+#             */
/*   Updated: 2025/06/16 17:42:02 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_outfile(t_cmd *cmd, t_token *token, int mode)
{
	if (cmd->fd_out > -1)
		close(cmd->fd_out);
	if (mode == 1)
		cmd->fd_out = open(token->next->elem, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		cmd->fd_out = open(token->next->elem, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (cmd->fd_out == -1)
	{
		perror(token->next->elem);
		return (1);
	}
	return (0);
}

int	set_infile(t_cmd *cmd, t_token *token)
{
	if (cmd->fd_in)
		close(cmd->fd_in);
	cmd->fd_in = open(token->next->elem, O_RDONLY);
	if (cmd->fd_in == -1)
	{
		perror(token->next->elem);
		return (1);
	}
	return (0);
}

int	set_hd(t_cmd *cmd, t_token *token, t_mshell *mshell, t_parser *parser)
{
	if (cmd->fd_in > -1)
		close(cmd->fd_in);
	ft_handle_hd(mshell, parser, token->next, cmd);
	if (cmd->fd_in == -1)
	{
		perror(token->next->elem);
		return (1);
	}
	return (0);
}
