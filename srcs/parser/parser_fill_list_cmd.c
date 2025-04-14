/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_list_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:36:24 by pbret             #+#    #+#             */
/*   Updated: 2025/04/14 18:41:29 by pbret            ###   ########.fr       */
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

void	ft_handle_redir(t_token *token, t_cmd *cmd)
{
	while (token->token != END)
	{
		if (token->token == F_IN)
			ft_get_infile(cmd, token);
		else if (token->token == F_OUT || token->token == F_APP)
			ft_get_outfile(cmd, token);
		token = token->next;
	}
}

void	ft_fill_list_cmd(t_parser *parser/* , t_mnode **ml */)
{
	t_token	*token;
	t_cmd	*cmd;
	
	token = parser->list_token;
	cmd = parser->list_cmd;
	while (token->token != END)
	{
		if (token->token == PIPE)
			cmd = cmd->next;
		ft_handle_redir(token, cmd);
		/* ft_handle_cmd(token, cmd, parser, ml);
		ft_handle_hd(token, cmd, parser, ml); */
		token = token->next;
	}
}

// bash-5.1$ cat infile 
// bonjour Paul
// salut Jo!
// 42 est un etablissement genial !!!


// bash-5.1$ < infile grep 'o'|wc -l>outfile

// bash-5.1$ < in"file" grep 'o' | wc -l > outfile

// < ; "infile" grep 'o' ; | ; wc -l ; > ; outfile
// cat ; < ; Makefile
// ../..//../