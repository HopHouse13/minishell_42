/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clear_and_expand.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:34:58 by pab               #+#    #+#             */
/*   Updated: 2025/05/20 12:15:56 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Expansion ($VAR → contenu brut dans l'input)
// dans double quote -> l'echappemment a effet uniquement sur [ " $ / ]    C'EST TOUT
// Quand une variable d'env doit etre expand mais n'existe pas -> elle est renplace par une chaine vide  (rien)

// CHOSES A FAIRE:
// - EXPAND selon les quotes et les carac d'echappement puis mettre entre [...] l'expansion pour bien les identifier pour les conserver brut.
// - supp quotes sauf avec '\' devant(dans double quote ou exterieur) ou simple quote dans double quote et pas a l'interieur de[...] VAR expand ni tout ce qui il  ya entre simple quote.
// - supp "\" et "[" "]" 	Pour '\'	-> dans les double_q : conservation sauf si devant " ou $ ou / (car il est actif pour ce cas la)
//										-> dans simple_q : conservation totale
//										-> a l'exterieur : disparition total car actif pour tout

void	ft_clear_and_expand(t_mshell *mshell, t_parser *parser)
{	ft_printf("\n\tvvvvvvvvvvvvvvvvvvv EXPAND_CLEAR vvvvvvvvvvvvvvvvvvvv\n");
	
	ft_printf("\n\t------------------ expand_markers -------------------\n\n");
	ft_mark_expand(mshell, parser);
	ft_print_list_token(parser->list_token); // ASUPP
	
	ft_printf("\n\t---------- clear_escape_char_and_quotes -------------\n\n");
	ft_clear_elems(mshell, parser);
	ft_print_list_token(parser->list_token); // ASUPP

	ft_printf("\n\t--------------------- expand ------------------------\n\n");
	ft_expand_list(mshell, parser);
	ft_print_list_token(parser->list_token); // ASUPP
}
