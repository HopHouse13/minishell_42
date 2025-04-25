/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_hd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:12:48 by pbret             #+#    #+#             */
/*   Updated: 2025/04/24 20:33:40 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_get_hd(t_cmd *lt_cmd, t_token *lt_token)
{
	if (lt_cmd->fd_hd != -1)
		close(lt_cmd->fd_hd);
	lt_cmd->fd_hd = open(lt_token->elem, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (lt_cmd->fd_hd == -1)
	{
		perror(lt_token->elem);
		//exit_status = 1;
	}
	lt_cmd->delim_hd = lt_token->elem;
}

bool	ft_srch_quotes(char *elem)
{
	int	i;

	i = -1;
	while (elem[++i])
	{
		if (elem[i] == '\'' || elem[i] == '\"')
			return(true);
	}
	return (false);
}

// ft_srch_quotes check si il u a au moins une quotes dansle DELIM
// si il y en a, je stock l'info dans expand_hd et ft_rm... les retire
void	ft_handle_hd(t_parser *parser, t_mnode **ml)
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
			lt_token->elem = ft_rm_quotes_and_esc(parser, lt_token->elem, ml);
			ft_get_hd(lt_cmd, lt_token);
			ft_heredoc(lt_cmd, ml);
		}
		lt_token = lt_token->next; 
	}
}
