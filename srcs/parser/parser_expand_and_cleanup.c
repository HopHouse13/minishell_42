/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_and_cleanup.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:34:58 by pab               #+#    #+#             */
/*   Updated: 2025/04/04 18:39:18 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*ft_merge(char *str, t_parser parser, t_mnode **ml)
// {
// 	int		i;
// 	char	**tab;
// 	char	*str_merged;
	
// 	i = -1;
// 	while (str[++i])
// 	{
		
// 	}
// 	return (str_merged)
// }

// char	*ft_add_brack(char *str, t_mnode **ml)
// {
// 	return ft_strjoin_ml(ft_strjoin_ml("[", str, ml), "]", ml);
// }

// char	*ft_expand(char *elem, int i, t_parser *parser, t_mnode **ml)
// {
// 	int		start_name;
// 	char	*var_name;
// 	char	*value_ptr;
// 	char	*var_expanded;
	
// 	start_name = ++i;
// 	/* if (elem[(*i)] == '?') // dernier exit status
// 		return (ft_itoa_ml(exit_status)); */
// 	if (elem[i] == '$') // PID du processus en cours
// 		return (ft_itoa(getpid()));
// 	if (!ft_isalpha(elem[i]) && elem[i] != '_')
// 		return (NULL);
// 	while (ft_isalnum(elem[i]) || elem[i] == '_')
// 		i++;
// 	parser->end = i;
// 	var_name = ft_substr_ml(elem, start_name, parser->end, ml);
// 	if (!var_name)
// 		return (NULL);
// 	printf(">>>%s\n\n", var_name);
// 	value_ptr = getenv(var_name);
// 	if (value_ptr)
// 		var_expanded = ft_strdup_ml(value_ptr, ml);
// 	else
// 		var_expanded = ft_strdup_ml("", ml);
// 	return (var_expanded);
// }
// // split + Join
// // dup + join
// void	ft_expand_list(t_parser *parser, t_mnode **ml)
// {
// 	int		i;
// 	t_token *tmp;
// 	char	*var_exp;
	
// 	tmp = parser->list_token;
// 	while (tmp && tmp->token != END)
// 	{
// 		i = -1;
// 		while (tmp->elem[++i])
// 		{
// 			/* if(i , ) */
// 			ft_inside_quotes_parser(parser, tmp->elem[i]);
// 			if (tmp->elem[i] == '$' && parser->simple_q == OUT_Q
// 				&& tmp->token != DELIM_HD && (i == 0
// 				|| (tmp->elem[i - 1] != '\\' 
// 				&& tmp->elem[i - 1] != '$')))
// 			{
// 				parser->start = i;
// 				var_exp = ft_add_brack(ft_expand(tmp->elem, i, parser, ml), ml);
// 				printf("\nexppanded : %s\n\n", var_exp);
// 				//ft_merge(var_exp, parser, ml);
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// }

// Expansion ($VAR → contenu brut dans l'input)
// dans double quote -> l'echappemment a effet uniquement sur [ " $ / ]    C'EST TOUT
// Quand une variable d'env doit etre expand mais n'existe pas -> elle est renplace par une chaine vide  (rien)

// CHOSES A FAIRE:
// - EXPAND selon les quotes et les carac d'echappement puis mettre entre [...] l'expansion pour bien les identifier pour les conserver brut.
// - supp quotes sauf avec '\' devant(dans double quote ou exterieur) ou simple quote dans double quote et pas a l'intieur de[...] VAR expand ni tout ce qui il  ya entre simple quote.
// - supp "\" et "[" "]" 	Pour '\'	-> dans les double_q : conservation sauf si devant " ou $ ou / (car il est actif pour ce cas la)
//										-> dans simple_q : conservation totale
//										-> a l'exterieur : disparition total car actif pour tout

// void	ft_expand_list_and_cleanup(t_parser *parser, t_mnode **ml)
// {
// 	ft_expand_list(parser, ml);			// >> delim -> ne pas expand si HD avant
// 	// ft_delete_quotes(parser, ml);
// 	// ft_clear_escape_character(parser, ml);
// } 