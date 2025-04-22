/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_list_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:36:24 by pbret             #+#    #+#             */
/*   Updated: 2025/04/17 15:45:43 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_fill_list_cmd(t_parser *parser, t_mnode **ml)
{
	ft_handle_redir(parser);
	ft_handle_cmd(parser, ml);
	// ft_handle_hd(token, cmd, parser, ml);
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