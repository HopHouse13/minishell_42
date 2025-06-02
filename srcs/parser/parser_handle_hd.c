/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_hd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:12:48 by pbret             #+#    #+#             */
/*   Updated: 2025/06/02 17:52:48 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_get_hd(t_mshell *mshell, t_cmd *lt_cmd, t_token *lt_token)
{
	if (lt_cmd->fd_hd != -1)
		close(lt_cmd->fd_hd);
	lt_cmd->fd_hd = open("/tmp/heredoc_tmp.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (lt_cmd->fd_hd == -1)
		return (ft_fd_err(mshell, "heredoc")); // pas bon
	lt_cmd->delim_hd = lt_token->elem;
	return (true);
}

// ft_srch_quotes check si il u a au moins une quotes dans le DELIM
// si il y en a, je stock l'info dans expand_hd et ft_rm... les retirer
bool	ft_handle_hd(t_mshell *mshell, t_parser *parser)
{
	t_token	*lt_token;
	t_cmd	*lt_cmd;
	
	lt_token = parser->list_token;
	lt_cmd = parser->list_cmd;
	while (lt_token->token != END)
	{
		if (lt_token->token == PIPE)
			lt_cmd = lt_cmd->next;
		else if (lt_token->token == DELIM)
		{
			lt_cmd->expand_hd = ft_srch_quotes(lt_token->elem);
			lt_token->elem = ft_remove(mshell, parser, lt_token->elem);
			if (!ft_get_hd(mshell, lt_cmd, lt_token))
				return (false);
			ft_heredoc(mshell, lt_cmd); // pas au bon endroit
		}
		lt_token = lt_token->next; 
	}
	return (true);
}
