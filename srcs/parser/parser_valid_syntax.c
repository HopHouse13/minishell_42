/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_valid_syntax.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:11:43 by pab               #+#    #+#             */
/*   Updated: 2025/05/29 02:22:46 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_valid_pipes(t_parser *parser)
{
	t_token	*tmp;
	bool	pipe;

	pipe =false;
	tmp = parser->list_token;
	if (tmp && tmp->token == PIPE)
		return (false);
	while (tmp->next && tmp->next->token != END)
	{
		if (tmp->token == PIPE && pipe)
			return (false);
		if (tmp->token == PIPE && !pipe)
			pipe = true;
		else
			pipe = false;
		tmp= tmp->next;
	}
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
		if ((tmp->token == CMD || tmp->token == BI) && !cmd)
			cmd = true;
		else if (tmp->token == ARG && !cmd)
		{
			fprintf(stderr,"minishell: syntax error near unexpected token %s\n", tmp->elem);
			// exit code ?
			return (false);
		}
		else if (tmp->token == PIPE)
			cmd = false;
		tmp = tmp->next;
	}
	return (true);
}

bool	ft_valid_redirs(t_parser *parser)
{
	t_token	*tmp;

	tmp = parser->list_token;
	while (tmp->next && tmp->next->token != END)
	{
		if ((tmp->token == R_IN && tmp->next->token != F_IN)
			|| (tmp->token == R_OUT && tmp->next->token != F_OUT)
			|| (tmp->token == APPEND && tmp->next->token != F_APP)
			|| (tmp->token == HD && tmp->next->token != DELIM))
			return (false); // g_exit_code = 258 ???
		tmp= tmp->next;
	}
	if (tmp && (tmp->token == R_IN || tmp->token == R_OUT
		|| tmp->token == APPEND || tmp->token == HD))
		return (false);// g_exit_code = 258  ???
	return (true);
}

// on pourrait retourner tmp->elem du noeud ou il ya une erreur pour le message
// d'erreur a retourner. a voir.
// check si il y a un pipe en premier ou en dernier de l'input.
// check si il y a plus d'une cmd par pipe.
// Check si toutes les redir sont suivis du bon token.
bool	ft_valid_syntax( t_mshell *mshell, t_parser *parser)
{
	if (!ft_valid_pipes(parser))
		ft_err(mshell," PROBLEME\n", "|", 1); // temporaire
	if (!ft_valid_cmds(parser))
		return (printf("cmds_issue\n"), false);
	if (!ft_valid_redirs(parser))
		return (printf("redir_issue\n"), false);
	return (true);
}
