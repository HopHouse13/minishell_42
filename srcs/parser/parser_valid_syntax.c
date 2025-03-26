/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_valid_syntax.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:11:43 by pab               #+#    #+#             */
/*   Updated: 2025/03/26 02:57:07 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_valid_pipes(t_parser *parser)
{
	t_token	*tmp;

	tmp = parser->list_token;
	if (tmp && tmp->token == PIPE)
		return (false);
	while (tmp->next && tmp->next->token != END)
		tmp= tmp->next;
	if (tmp->token == PIPE)
		return (false);
	return (true);
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

bool	ft_valid_redirs(t_parser *parser)
{
	t_token	*tmp;
	
	tmp = parser->list_token;
	if ((tmp->token == R_IN && !ft_cmds(ft_find_next_cmd(tmp)))
		|| tmp->token == R_OUT || tmp->token == APPEND || tmp->token == HD)
		return (false);
	while (tmp->next && tmp->next->token != END)
	{
		if ((tmp->token == R_IN && tmp->next->token != F_IN)
			|| (tmp->token == R_OUT && tmp->next->token != F_OUT)
			|| (tmp->token == APPEND && tmp->next->token != F_APP)
			|| (tmp->token == HD && tmp->next->token != DELIM_HD))
			return (false);
		tmp= tmp->next;
	}
	if (tmp->token == R_IN || tmp->token == R_OUT
		|| tmp->token == APPEND || tmp->token == HD)
		return (false);
	return (true);
}

// on pourrait retourner tmp->elem du noeud ou il ya une erreur pour le message d'errewur a retourner. a voir.
bool	ft_valid_syntax(t_parser *parser)
{
	if (!ft_valid_pipes(parser))
		return (false);
	if (!ft_valid_cmds(parser))
		return (false);
	if (!ft_valid_redirs(parser))
		return (false);
	return (true);
}