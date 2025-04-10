/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_and_cleanup.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:34:58 by pab               #+#    #+#             */
/*   Updated: 2025/04/10 17:36:22 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_insert_marker(char *str, int i, t_mnode **ml)
{
	char	*result;
	int		j;
	int		k;
	
	result = ft_malloc_list(sizeof(char) * ft_strlen(str) + 2, ml);
	j = 0;
	k = 0;
	while (str[j])
	{
		if (k == i + 1)
			result[k++] = '!';
		else
			result[k++] = str[j++];
	}
	result[k] = '\0';
	printf("result_marker : %s\n", result);
	return (result);
}

char	*ft_marker(char *str, t_type token, t_parser *parser, t_mnode **ml)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		ft_inside_quotes_parser(parser, str, i);
		if (str[i] == '$' && parser->simple_q == OUT && token != DELIM
			&& (i == 0 || !ft_effect_escape_parser(parser, str, i)))
			str = ft_insert_marker(str, i, ml);
	}
	return (str);
}

void	ft_mark_expand(t_parser *parser, t_mnode **ml)
{
	t_token	*tmp;
	
	tmp = parser->list_token;
	while (tmp && tmp->token != END)
	{
		tmp->elem = ft_marker(tmp->elem, tmp->token, parser, ml);
		tmp = tmp->next;
	}
}




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
	ft_mark_expand(parser, ml);
	ft_print_list_token(parser->list_token);
	ft_delete_quotes_and_escape_char(parser, ml);
	ft_expand_list(parser, ml);	// >> delim -> ne pas expand si HD avant
	ft_print_list_token(parser->list_token);
	// ft_print_list_token(parser->list_token);
} 