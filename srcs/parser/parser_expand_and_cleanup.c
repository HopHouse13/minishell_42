/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_and_cleanup.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:34:58 by pab               #+#    #+#             */
/*   Updated: 2025/04/09 19:30:31 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_delete_quotes(t_parser *parser, t_mnode **ml)
{
	t_token	*tmp;
	
	tmp = parser->list_token;
	while (tmp && tmp->token != END)
	{
		tmp->elem = ft_remove_quotes(parser, tmp->elem, ml);
		tmp = tmp->next;
	}
}

/* void	ft_clear_escape_character(t_parser *parser, t_mnode **ml)
{
	t_token	*tmp;
	
	tmp = parser->list_token;
	while (tmp && tmp->token != END)
	{
		tmp->elem = ft_remove_quotes(parser, tmp->elem, ml);
		tmp = tmp->next;
	}
} */

// Expansion ($VAR → contenu brut dans l'input)
// dans double quote -> l'echappemment a effet uniquement sur [ " $ / ]    C'EST TOUT
// Quand une variable d'env doit etre expand mais n'existe pas -> elle est renplace par une chaine vide  (rien)

// CHOSES A FAIRE:
// - EXPAND selon les quotes et les carac d'echappement puis mettre entre [...] l'expansion pour bien les identifier pour les conserver brut.
// - supp quotes sauf avec '\' devant(dans double quote ou exterieur) ou simple quote dans double quote et pas a l'interieur de[...] VAR expand ni tout ce qui il  ya entre simple quote.
// - supp "\" et "[" "]" 	Pour '\'	-> dans les double_q : conservation sauf si devant " ou $ ou / (car il est actif pour ce cas la)
//										-> dans simple_q : conservation totale
//										-> a l'exterieur : disparition total car actif pour tout

void	ft_expand_list_and_cleanup(t_parser *parser, t_mnode **ml)
{ft_printf("\n\t****************** expand_&_clear ********************\n\n");
	ft_expand_list(parser, ml);	// >> delim -> ne pas expand si HD avant
	ft_print_list_token(parser->list_token);
	ft_delete_quotes(parser, ml);
	ft_print_list_token(parser->list_token);
	// ft_clear_escape_character(parser, ml);
} 