/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:19:55 by pab               #+#    #+#             */
/*   Updated: 2025/06/02 12:41:46 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_get_fd_outfile(t_mshell *mshell, t_cmd *cmd, t_token *token)
{
	if (cmd->fd_out > -1)
		close(cmd->fd_out);
	if (token->token == F_OUT)
		cmd->fd_out = open(token->elem, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->fd_out == -1)
		return (ft_fd_err(mshell, token->elem));
	return (true);	
}

bool	ft_get_fd_infile(t_mshell *mshell, t_cmd *cmd, t_token *token)
{
	if (cmd->fd_in > -1)
		close(cmd->fd_in);
	cmd->fd_in = open(token->elem, O_RDONLY);
	if (cmd->fd_in == -1)
		return (ft_fd_err(mshell, token->elem));
	return (true);
}	

bool	ft_handle_redir(t_mshell *mshell, t_parser *parser)
{
	t_token	*list_token;
	t_cmd	*list_cmd;
	
	list_token = parser->list_token;
	list_cmd = parser->list_cmd;
	while (list_token->token != END)
	{
		if (list_token->token == PIPE)
			list_cmd = list_cmd->next;
		if (list_token->token == F_IN)
		{
			if (!ft_get_fd_infile(mshell, list_cmd, list_token))
				return (false);
		}
		else if (list_token->token == F_OUT || list_token->token == F_APP)
		{
			if (!ft_get_fd_outfile(mshell, list_cmd, list_token))
				return (false);
		}
		list_token = list_token->next;
	}
	return (true);
}
