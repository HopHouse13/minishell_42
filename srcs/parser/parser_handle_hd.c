/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_hd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:12:48 by pbret             #+#    #+#             */
/*   Updated: 2025/06/20 11:32:56 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_get_hd(t_mshell *mshell, t_cmd *lt_cmd, t_token *lt_token)
{
	if (lt_cmd->fd_in > -1)
		close(lt_cmd->fd_in);
	lt_cmd->fd_in = open("./heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (lt_cmd->fd_in == -1)
		return (ft_fd_err(mshell, "heredoc"));
	lt_cmd->delim_hd = lt_token->elem;
	return (true);
}

void	ft_handle_hd(t_mshell *ms, t_parser *prs, t_token *lt_t, t_cmd *lt_cmd)
{
	lt_cmd->expand_hd = ft_srch_quotes(lt_t->elem);
	lt_t->elem = ft_remove(ms, prs, lt_t->elem);
	if (!ft_get_hd(ms, lt_cmd, lt_t))
		ft_mem_err(ms);
	ft_signals(3);
	ft_heredoc(ms, lt_cmd);
	if (lt_cmd->fd_in != -1)
		close(lt_cmd->fd_in);
	ft_signals(2);
	lt_cmd->fd_in = open("./heredoc.txt", O_RDONLY);
	if (!lt_cmd->fd_in)
		ft_mem_err(ms);
}

// ft_srch_quotes check si il u a au moins une quotes dans le DELIM
// si il y en a, je stock l'info dans expand_hd et ft_rm... les retirer
// bool	ft_handle_hd(t_mshell *mshell, t_parser *parser)
// {
// 	t_token	*lt_token;
// 	t_cmd	*lt_cmd;

// 	lt_token = parser->list_token;
// 	lt_cmd = parser->list_cmd;
// 	while (lt_token->token != END)
// 	{
// 		if (lt_token->token == PIPE)
// 			lt_cmd = lt_cmd->next;
// 		else if (lt_token->token == DELIM)
// 		{
// 			lt_cmd->expand_hd = ft_srch_quotes(lt_token->elem);
// 			lt_token->elem = ft_remove(mshell, parser, lt_token->elem);
// 			if (!ft_get_hd(mshell, lt_cmd, lt_token))
// 				return (false);
// 			ft_heredoc(mshell, lt_cmd); // pas au bon endroit ou pas
// 		}
// 		lt_token = lt_token->next;
// 	}
// 	return (true);
// }
