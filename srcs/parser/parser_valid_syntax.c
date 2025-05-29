/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_valid_syntax.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:11:43 by pab               #+#    #+#             */
/*   Updated: 2025/05/29 18:06:41 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_valid_pipes(t_parser *parser)
{
	t_token	*tmp;
	bool	pipe;

	pipe =false;
	tmp = parser->list_token;
	if (tmp && tmp->token == PIPE)
		return (tmp->elem);
	while (tmp->next && tmp->next->token != END)
	{
		if (tmp->token != PIPE)
			pipe = false;
		else if (tmp->token == PIPE && pipe)
			return (tmp->elem);
		else if (tmp->token == PIPE && !pipe)
			pipe = true;
		tmp= tmp->next;
	}
	if (tmp->token == PIPE)
		return (tmp->elem);
	return (NULL);
}

char	*ft_valid_cmds(t_parser *parser)
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
			return (tmp->elem);
		else if (tmp->token == PIPE)
			cmd = false;
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_valid_redirs(t_parser *parser)
{
	t_token	*tmp;

	tmp = parser->list_token;
	while (tmp->next && tmp->next->token != END)
	{
		if ((tmp->token == R_IN && tmp->next->token != F_IN)
			|| (tmp->token == R_OUT && tmp->next->token != F_OUT)
			|| (tmp->token == APPEND && tmp->next->token != F_APP)
			|| (tmp->token == HD && tmp->next->token != DELIM))
				return (tmp->elem);
		tmp= tmp->next;
	}
	if (tmp && (tmp->token == R_IN || tmp->token == R_OUT
		|| tmp->token == APPEND || tmp->token == HD))
			return (tmp->elem);
	return (NULL);
}

// on pourrait retourner tmp->elem du noeud ou il ya une erreur pour le message
// d'erreur a retourner. a voir.
// check si il y a un pipe en premier ou en dernier de l'input.
// check si il y a plus d'une cmd par pipe.
// Check si toutes les redir sont suivis du bon token.
bool	ft_valid_syntax(t_mshell *mshell, t_parser *parser)
{
	if (ft_valid_pipes(parser))
		return (ft_syntax_err(mshell, ft_valid_pipes(parser), 2));
	if (ft_valid_cmds(parser))
		return (ft_syntax_err(mshell, ft_valid_cmds(parser), 2));
	if (ft_valid_redirs(parser))
		return (ft_syntax_err(mshell, ft_valid_redirs(parser), 2));
	return (true);
}
