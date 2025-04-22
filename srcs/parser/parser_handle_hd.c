/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_hd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:12:48 by pbret             #+#    #+#             */
/*   Updated: 2025/04/22 19:23:02 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_get_hd(t_cmd *cmd, t_token *token)
{
	if (cmd->fd_hd != -1)
		close(cmd->fd_hd);
	cmd->fd_hd = open(token->elem, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmd->fd_hd == -1)
	{
		perror(token->elem);
		//exit_status = 1;
	}
	cmd->delim_hd = token->elem;
}


void	ft_handle_hd(t_parser *parser)
{
	t_token	*list_token;
	t_cmd	*list_cmd;
	
	list_token = parser->list_token;
	list_cmd = parser->list_cmd;
	while (list_token->token != END)
	{
		if (list_token->token == PIPE)
			list_cmd = list_cmd->next;
		else if (list_token->token == DELIM)
			ft_get_hd(list_cmd, list_token);
		list_token = list_token->next; 
	}
}