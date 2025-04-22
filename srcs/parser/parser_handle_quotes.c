/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:17:37 by pbret             #+#    #+#             */
/*   Updated: 2025/04/13 16:34:38 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Met à jour l'état d'un type de guillemet (simple ou double).
// Si le guillemet est ouvert, il est fermé et le marqueur est mis à OUT.
// S'il est fermé, il est ouvert et le marqueur est mis à OUT seulement si
// aucun autre guillemet n'était déjà actif.
void	ft_status_update_parser(bool *quote, bool *mark, bool *flag)
{
	if (*quote == IN)
	{
		*quote = OUT;
		*mark = OUT;
	}	
	else 
	{
		*quote = IN;
		if (*flag == OUT)
		{
			*mark = OUT;
			*flag = IN;
		}
	}
}

// Gère l'état des guillemets dans le parser en fonction du caractère analysé.
// Vérifie l'ouverture et la fermeture des guillemets simples et doubles,
// en prenant en compte les caractères d'échappement.
// Retourne l'état du marqueur `mark_q` après traitement du caractère.
//  si 1 -> IN ; si 0 -> OUT;
bool	ft_inside_quotes_parser(t_parser *parser, char *str, int i)
{
	if (i == 0)
	{
		parser->simple_q = OUT;
		parser->double_q = OUT;
		parser->flag_q = OUT;
		parser->mark_q = OUT;
	}
	if (parser->flag_q == IN)
	{
		parser->flag_q = OUT;
		parser->mark_q = IN;
	}
	if (!ft_effect_escape_parser(parser, str, i))
	{
		if (str[i] == '\'' && parser->double_q == OUT)
			ft_status_update_parser(&parser->simple_q,
			&parser->mark_q, &parser->flag_q);
		else if (str[i] == '\"' && parser->simple_q == OUT)
			ft_status_update_parser(&parser->double_q,
			&parser->mark_q, &parser->flag_q);
	}
	// printf("\tsimple_q: %d\tdouble_q: %d\tmark_q: %d\tchar [%c]\n", parser->simple_q, parser->double_q, parser->mark_q, str[i]);
	return (parser->mark_q);
}
