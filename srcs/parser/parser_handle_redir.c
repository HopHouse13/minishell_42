/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:19:55 by pab               #+#    #+#             */
/*   Updated: 2025/04/23 19:59:21 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_get_fd_outfile(t_cmd *lt_cmd, t_token *lt_token)
{
	if (lt_cmd->fd_out > -1)
		close(lt_cmd->fd_out);
	if (lt_token->token == F_OUT)
		lt_cmd->fd_out = open(lt_token->elem, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (lt_cmd->fd_out == -1)
	{
		perror(lt_token->elem);
		//exit_status = 1;
	}
}

void	ft_get_fd_infile(t_cmd *cmd, t_token *token)
{
	if (cmd->fd_in > -1)
		close(cmd->fd_in);
	cmd->fd_in = open(token->elem, O_RDONLY);
	if (cmd->fd_in == -1)
	{
		perror(token->elem);
		//exit_status = 1;
	}
}

void	ft_handle_redir(t_parser *parser)
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
			ft_get_fd_infile(list_cmd, list_token);
		else if (list_token->token == F_OUT || list_token->token == F_APP)
			ft_get_fd_outfile(list_cmd, list_token);
		list_token = list_token->next;
	}
}