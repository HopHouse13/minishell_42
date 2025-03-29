/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:48:36 by pbret             #+#    #+#             */
/*   Updated: 2025/03/29 18:37:13 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*ft_parser(t_mshell *mshell, t_token *list_token, t_mnode **ml)
{
	t_parser	parser;
	
	ft_init_parser(mshell, &parser, list_token);
	if (ft_valid_syntax(&parser, ml))
	{printf("\nSUCCESS\n\n");
		ft_init_list_cmd(&parser, ml);
		// ft_expand_and_cleanup(&parser, ml);
		//ft_fill_list_cmd(&parser, ml);
		return (parser.list_cmd);
	}
	printf("\nFAILURE\n\n");
	return (NULL);
}

// ATTENTION -> lors de la comparaison des commandes qui prennent une redir_in (comme cat), le '\' est mal gere. (< in "ca\t")
// exterieur:		si actif -> agit puis disparait
//					si inactif -> disparait
//
// dans double_q: 	si actif -> agit puis disparait
//					is inactif -> est affichie comme un carac std

// echo c\at
// cat

// echo c\\at
// c\at

// echo "c\at"
// c\at

// echo "c\\at" $ \ "
// c\at
