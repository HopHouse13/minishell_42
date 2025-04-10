/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_and_cleanup.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:34:58 by pab               #+#    #+#             */
/*   Updated: 2025/04/10 12:26:53 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

ft_insert_marker(str, i, ml);

void	ft_marker(char **str, t_type token, t_parser *parser, t_mnode **ml)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && parser->simple_q == OUT && token != DELIM
			&& (i == 0 || !ft_effect_escape_parser(parser, str, i)))
			ft_insert_marker(str, i, ml);
	}
}

void	ft_mark_expand(t_parser *parser, t_mnode **ml)
{
	t_token	*tmp;

	tmp = parser->list_token;
	while (tmp && tmp->token != END)
	{
		tmp-eft_marker(&tmp->elem, tmp->token, parser, ml);
		tmp = tmp->next;
	}
}

/* bool	ft_inside_bracket(t_parser *parser, char *str, int i)
{	
	parser->mark_b = false;
	if (str[i] == '[')
	parser->mark_b = true;
	else if (str[i] == ']')
	parser->mark_b = false;
	return(parser->mark_b);
}

char	*ft_remove_quotes(t_parser *parser, char *str, t_mnode **ml)
{
	int		i;
	int		j;
	size_t	count_without_q;
	char	*str_without_q;
	
	i = -1;
	count_without_q = 0;
	while (str[++i])
		if (ft_inside_quotes_parser(parser, str, i) || ft_inside_bracket(parser, str, i)
			|| (str[i] != '\'' 	&& str[i] != '\"'))
			count_without_q++;
	str_without_q = ft_malloc_list(sizeof(char) * count_without_q + 1, ml);
	i = -1;
	j = 0;
	while (str[++i])
		if ((ft_inside_quotes_parser(parser, str, i))|| ft_inside_bracket(parser, str, i)
			|| (str[i] != '\'' && str[i] != '\"'))
			str_without_q[j++] = str[i];
	str_without_q[j] = '\0';
	return (str_without_q);
}

char	*ft_remove_brackets(char *str, t_mnode **ml)
{
	int		i;
	int		j;
	size_t	count_without_b;
	char	*str_without_b;
	
	i = -1;
	count_without_b = 0;
	while (str[++i])
		if (str[i] != '[' && str[i] != ']')
			count_without_b++;
	str_without_b = ft_malloc_list(sizeof(char) * count_without_b + 1, ml);
	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] != '[' && str[i] != ']')
			str_without_b[j++] = str[i];
	str_without_b[j] = '\0';
	return (str_without_b);
}

void	ft_delete_quotes_and_brackets(t_parser *parser, t_mnode **ml)
{
	t_token	*tmp;
	
	tmp = parser->list_token;
	while (tmp && tmp->token != END)
	{
		tmp->elem = ft_remove_quotes(parser, tmp->elem, ml);
		tmp->elem = ft_remove_brackets(tmp->elem, ml);
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
	ft_mark_expand(parser, ml);
	ft_expand_list(parser, ml);	// >> delim -> ne pas expand si HD avant
	ft_print_list_token(parser->list_token);
/* 	ft_delete_quotes_and_brackets(parser, ml);
	ft_print_list_token(parser->list_token); */
} 