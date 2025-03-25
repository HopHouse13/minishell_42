/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_valid_syntax.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:11:43 by pab               #+#    #+#             */
/*   Updated: 2025/03/25 21:07:25 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_valid_redirs(t_parser *parser)
{
	t_token	*tmp;
	
	tmp = parser->list_token;
	while (tmp->token == END)
}

bool	ft_valid_pipes(t_parser *parser)
{
	t_token	*tmp;

	tmp = parser->list_token;
	if (tmp->token == PIPE)
		return (false);
	while (tmp->next->token != END)
		tmp= tmp->next;
	if (tmp->token == PIPE)
		return (false);
}

bool	ft_valid_cmds(t_parser *parser)
{
	t_token *tmp;
	bool	cmd;
	
	cmd = false;
	tmp = parser->list_token;
	while (tmp->token != END)
	{
		if (tmp->token == CMD && cmd == true)
		{
			fprintf(stderr,"minishell: syntax error near unexpected token %s\n", tmp->elem);
			// exit code ?
			return (false);
		}
		if (tmp->token == CMD && cmd == false)
			cmd = true;
		if (tmp->token == PIPE)
			cmd = false;
		tmp = tmp->next;
	}
	return (true);
}

bool	ft_valid_syntax(t_parser *parser)
{
	if (!ft_valid_pipes(parser))
		return (false);
	if (!ft_valid_cmds(parser))
		return (false);
	if (!ft_valid_redir(parser))
		return (false);
	return (true);
}