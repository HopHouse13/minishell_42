/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_list_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:36:24 by pbret             #+#    #+#             */
/*   Updated: 2025/03/24 21:35:55 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_deletion_quotes(char *str, t_mnode **ml)
{
	int		i;
	int		j;
	int		count_other_quotes;
	char	*tmp;
	
	i = -1;
	count_other_quotes = 0;
	tmp = str;
	while (tmp[++i])
	{printf("test1\n");
		if (tmp[i] != '\'' && tmp[i] != '\"')
			count_other_quotes++;
	}
	str = ft_malloc_list(sizeof(char) * count_other_quotes + 1, ml);
	i = -1;
	j = -1;
	while (tmp[++i])
	{	
		if (tmp[i] != '\'' && tmp[i] != '\"')
			str[++j] = tmp[i];
	}
	ft_free_one_node_ml(tmp, ml);
	printf("str sans quotes : %s\n", str);
}

/* void	ft_build_tab_cmd(t_token *token, t_cmd *cmd, t_mnode **ml)
{
	
} */

void	ft_fill_list_cmd(t_parser *parser, t_mnode **ml)
{
	t_token	*tmp_token;
	t_cmd	*tmp_cmd;
	
	tmp_token = parser->list_token;
	tmp_cmd = parser->list_cmd;
	while (tmp_token->token != END || tmp_cmd) // pas sur de ca... 
	{
		ft_deletion_quotes(tmp_token->elem, ml);
		tmp_token = tmp_token->next; // ASUPP
		/* if (tmp_token->token == PIPE && tmp_cmd->next)
			tmp_cmd = tmp_cmd->next;
 		else if (tmp_token->token == REDIR_IN ||
				tmp_token->token == REDIR_OUT ||
 				tmp_token->token == APPEND)
 			ft_build_list_redir(tmp_token, tmp_cmd, ml);
 		else if (tmp_token->token == HD)
 			ft_build_list_hd(tmp_token, tmp_cmd, ml);
 		else if (tmp_token->token == ELEM)
 			ft_build_tab_cmd(tmp_token, tmp_cmd, ml);
		else
			tmp_token = tmp_token->next; */
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