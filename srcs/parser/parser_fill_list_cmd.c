/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_list_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:36:24 by pbret             #+#    #+#             */
/*   Updated: 2025/04/10 10:37:45 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* void	ft_build_tab_cmd(t_token *token, t_cmd *cmd, t_mnode **ml)
{
	
} */

// void	ft_fill_list_cmd(t_parser *parser, t_mnode **ml)
// {
// 	t_token	*tmp_token;
// 	t_cmd	*tmp_cmd;
	
// 	tmp_token = parser->list_token;
// 	tmp_cmd = parser->list_cmd;
// 	while (tmp_token->token != END || tmp_cmd) // pas sur de ca...
// 	{
// 		tmp_token = tmp_token->next; // ASUPP
// 		/* if (tmp_token->token == PIPE && tmp_cmd->next)
// 			tmp_cmd = tmp_cmd->next;
//  		else if (tmp_token->token == R_IN ||
// 				tmp_token->token == R_OUT ||
//  				tmp_token->token == APPEND)
//  			ft_build_list_redir(tmp_token, tmp_cmd, ml);
//  		else if (tmp_token->token == HD)
//  			ft_build_list_hd(tmp_token, tmp_cmd, ml);
//  		else if (tmp_token->token == ELEM)
//  			ft_build_tab_cmd(tmp_token, tmp_cmd, ml);
// 		else
// 			tmp_token = tmp_token->next; */
// 	}
// }
// bash-5.1$ cat infile 
// bonjour Paul
// salut Jo!
// 42 est un etablissement genial !!!


// bash-5.1$ < infile grep 'o'|wc -l>outfile

// bash-5.1$ < in"file" grep 'o' | wc -l > outfile

// < ; "infile" grep 'o' ; | ; wc -l ; > ; outfile
// cat ; < ; Makefile
// ../..//../