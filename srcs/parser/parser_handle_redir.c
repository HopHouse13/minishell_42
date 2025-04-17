/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:19:55 by pab               #+#    #+#             */
/*   Updated: 2025/04/17 14:20:39 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_get_outfile(t_cmd *cmd, t_token *token)
{
	if (cmd->outfile > -1)
		close(cmd->outfile);
	if (token->token == F_OUT)
		cmd->outfile = open(token->elem, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->outfile == -1)
	{
		perror(token->elem);
		//exit_status = 1;
	}
}

void	ft_get_infile(t_cmd *cmd, t_token *token)
{
	if (cmd->infile > -1)
		close(cmd->infile);
	cmd->infile = open(token->elem, O_RDONLY);
	if (cmd->infile == -1)
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
			ft_get_infile(list_cmd, list_token);
		else if (list_token->token == F_OUT || list_token->token == F_APP)
			ft_get_outfile(list_cmd, list_token);
		list_token = list_token->next;
	}
}