/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:17:37 by pbret             #+#    #+#             */
/*   Updated: 2025/04/08 11:59:01 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Met à jour l'état d'un type de guillemet (simple ou double).
// Si le guillemet est ouvert, il est fermé et le marqueur est mis à OUT_Q.
// S'il est fermé, il est ouvert et le marqueur est mis à OUT_Q seulement si
// aucun autre guillemet n'était déjà actif.
void	ft_status_update_parser(bool *quote, bool *mark, bool *flag)
{
	if (*quote == IN_Q)
	{
		*quote = OUT_Q;
		*mark = OUT_Q;
	}	
	else 
	{
		*quote = IN_Q;
		if (*flag == OUT_Q)
		{
			*mark = OUT_Q;
			*flag = IN_Q;
		}
	}
}

// Gère l'état des guillemets dans le parser en fonction du caractère analysé.
// Vérifie l'ouverture et la fermeture des guillemets simples et doubles,
// en prenant en compte les caractères d'échappement.
// Retourne l'état du marqueur `mark_q` après traitement du caractère.
//  si 1 -> IN_Q ; si 0 -> OUT_Q;
bool	ft_inside_quotes_parser(t_parser *parser, char *str, int i)
{
	if (i == 0)
	{
		parser->simple_q = OUT_Q;
		parser->double_q = OUT_Q;
		parser->flag_q = OUT_Q;
		parser->mark_q = OUT_Q;
	}
	if (parser->flag_q == IN_Q)
	{
		parser->flag_q = OUT_Q;
		parser->mark_q = IN_Q;
	}
	if (!ft_effect_escape_parser(parser, str, i))
	{
		if (str[i] == '\'' && parser->double_q == OUT_Q)
			ft_status_update_parser(&parser->simple_q,
			&parser->mark_q, &parser->flag_q);
		else if (str[i] == '\"' && parser->simple_q == OUT_Q)
			ft_status_update_parser(&parser->double_q,
			&parser->mark_q, &parser->flag_q);
	}
	printf("\tsimple_q: %d\tdouble_q: %d\tmark_q: %d\tchar [%c]\n", parser->simple_q, parser->double_q, parser->mark_q, str[i]);
	return (parser->mark_q);
}
